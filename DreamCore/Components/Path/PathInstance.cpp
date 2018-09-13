
#include <algorithm>

#include "PathInstance.h"

#include "../../Common/Constants.h"
#include "../../Utilities/String.h"
#include <tinyspline.h>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Dream
{

    PathInstance::PathInstance
    (shared_ptr<PathDefinition> definition, shared_ptr<SceneObjectRuntime> runtime)
        : IAssetInstance(definition,runtime),
          mWrapPath(true),
          mCurrentIndex(0),
          mUStep(0.05)
    {
        setLogClassName("PathInstance");
        auto log = getLog();
        log->trace("Constructing Object");

    }


    PathInstance::~PathInstance
    ()
    {
        auto log = getLog();
        log->trace("Destroying Object");
    }

    void PathInstance::recalculate
    ()
    {
        load("");
    }

    bool
    PathInstance::load
    (string)
    {
        auto animDef = dynamic_pointer_cast<PathDefinition>(mDefinition);
        auto log = getLog();
        log->info(
            "Loading {} spline with {} control points for {} ",
            animDef->getSplineType(),
            animDef->numberOfControlPoints(),
            getNameAndUuidString()
        );

        if (animDef->numberOfControlPoints() < 2)
        {
            log->warn("Skipping curve, not enough control points");
            mLoaded = true;
            return true;
        }

        loadExtraAttributes(mDefinition->getJson());

        mUStep = 1.0/(animDef->numberOfControlPoints()*animDef->getStepScalar());

        if (animDef->numberOfControlPoints() >= SPLINE_DIMENSIONS)
        {
            generate();
        }
        else
        {
            log->error("Not enough control points to generate spline");
        }

        mLoaded = true;
        return mLoaded;

    }

    void
    PathInstance::generate
    ()
    {
        auto animDef = dynamic_pointer_cast<PathDefinition>(mDefinition);
        auto log = getLog();
        auto splineType = animDef->getSplineTypeEnum();

        tsBSpline spline, derivative;
        tsReal *ctrlp;
        size_t i=0;

        mSplinePoints.clear();
        mSplineTangents.clear();
        mSplineDerivatives.clear();

        if (animDef->numberOfControlPoints() <= SPLINE_DIMENSIONS) return;

        ts_bspline_new(
            animDef->numberOfControlPoints(),
            SPLINE_DIMENSIONS, SPLINE_DEGREES,
            splineType, &spline);

        /* Setup control points. */
        ts_bspline_control_points(&spline, &ctrlp);

        for (json cp : *animDef->getControlPoints())
        {
            double x = cp[Constants::X];
            double y = cp[Constants::Y];
            double z = cp[Constants::Z];
            // Setup control points.
            ctrlp[i++] = x;
            ctrlp[i++] = y;
            ctrlp[i++] = z;
        }

        ts_bspline_set_control_points(&spline, ctrlp);
        free(ctrlp);

        ts_bspline_derive(&spline, 1, &derivative);

        // Stores our evaluation results.
        if (splineType == TS_CLAMPED)
        {
            tsDeBoorNet net1, net2, net3;
            tsReal *result1, *result2, *result3;
            tsReal *knots;

            /* draw spline */
            ts_bspline_control_points(&spline, &ctrlp);
            ts_bspline_knots(&spline, &knots);

            for (tsReal u = 0.0; u <= 1.0; u += mUStep)
            {
                ts_bspline_eval(&spline, u, &net1);
                ts_deboornet_result(&net1, &result1);
                ts_bspline_eval(&derivative, u, &net2);
                ts_deboornet_result(&net2, &result2);
                ts_bspline_eval(&derivative, u, &net3);
                ts_deboornet_result(&net3, &result3);

                log->info("Generating with u={}",u);
                log->info("Got spline point ({},{},{})",result1[0], result1[1], result1[2]);

                for (i = 0; i < ts_deboornet_dimension(&net2); i++)
                {
                    result2[i] = result1[i] + result2[i] / 6.0;
                    result3[i] = result1[i] - result3[i] / 6.0;
                }

                // tangent line
                vec3 point(result1[0],result1[1],result1[2]);
                vec3 tan1(result2[0],result2[1],result2[2]);
                vec3 tan2(result3[0],result3[1],result3[2]);

                mSplinePoints.push_back(point);
                mSplineTangents.push_back(getHeading(point, tan1,tan2));
                mSplineDerivatives.push_back(pair<vec3,vec3>(tan1,tan2));
            }

            ts_deboornet_free(&net1);
            ts_deboornet_free(&net2);
            ts_deboornet_free(&net3);
            free(result1);
            free(result2);
            free(result3);
            free(ctrlp);
            free(knots);
        }
        else if (splineType == TS_OPENED)
        {

        }
        else if (splineType == TS_BEZIERS)
        {

        }

        log->info("Finished Loading spline for {}",getNameAndUuidString());
    }

    void PathInstance::loadExtraAttributes(nlohmann::json)
    {

    }

    vector<pair<vec3, vec3> > PathInstance::getSplineDerivatives() const
    {
        return mSplineDerivatives;
    }

    bool PathInstance::getWrapPath() const
    {
        return mWrapPath;
    }

    void PathInstance::setWrapPath(bool wrapPath)
    {
        mWrapPath = wrapPath;
    }

    size_t PathInstance::getCurrentIndex() const
    {
        return mCurrentIndex;
    }

    void PathInstance::setCurrentIndex(size_t currentIndex)
    {
        mCurrentIndex = currentIndex;
    }

    Transform3D PathInstance::stepPath()
    {
        auto log = getLog();
        Transform3D retval;

        if (mSplinePoints.empty())
        {
            return retval;
        }

        mCurrentIndex++;

        if (mCurrentIndex >= mSplinePoints.size())
        {
            if (mWrapPath)
            {
                mCurrentIndex = 0;
            }
            else
            {
                mCurrentIndex = mSplinePoints.size()-1;
            }
        }


        vec3 thisPoint = mSplinePoints.at(mCurrentIndex);
        quat thisOrient = mSplineTangents.at(mCurrentIndex);

        retval.setTranslation(thisPoint);
        retval.setOrientation(thisOrient);
        vec3 ang = eulerAngles(thisOrient);
        log->trace("Got spline point {}/{} T({},{},{}) R({},{},{})",
            mCurrentIndex,mSplinePoints.size(),
            thisPoint.x, thisPoint.y, thisPoint.z,
            ang.x, ang.y, ang.z
        );
        return retval;

    }

    vector<vec3> PathInstance::getSplinePoints() const
    {
        return mSplinePoints;
    }

    vector<glm::quat> PathInstance::getSplineTangents() const
    {
       return mSplineTangents;
    }

    glm::vec3 PathInstance::getSplinePoint(int index) const
    {
        if (index >=0 && index < mSplinePoints.size())
        {
            return mSplinePoints.at(index);
        }
        return vec3(0);
    }

    double PathInstance::getUStep() const
    {
        return mUStep;
    }

    void PathInstance::setUStep(double uStep)
    {
        mUStep = uStep;
    }

    quat PathInstance::getHeading(vec3 point, vec3 t1, vec3 t2)
    {
        auto log = getLog();
        glm::mat4 mtx = glm::lookAt(t1,t2,vec3(0,1,0));
        quat q = quat(mtx);
        q.x = -q.x;
        q.y = -q.y;
        q.z = -q.z;

        return q;
    }

    const int PathInstance::SPLINE_DIMENSIONS = 3;
    const int PathInstance::SPLINE_DEGREES = 3;

} // End of Dream