/*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <algorithm>

#include "PathRuntime.h"

#include "../../Utilities/String.h"
#include "../../deps/tinyspline/tinyspline.h"
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Dream
{

    PathRuntime::PathRuntime
    (
        PathDefinition* definition,
        SceneObjectRuntime* runtime
    ) : DiscreteAssetRuntime(definition,runtime),
          mWrapPath(true),
          mCurrentIndex(0),
          mUStep(0.05)
    {
#ifdef DREAM_LOG
        setLogClassName("PathInstance");
        auto log = getLog();
        log->trace("Constructing Object");
#endif

    }

    PathRuntime::~PathRuntime
    ()
    {
#ifdef DREAM_LOG
        auto log = getLog();
        log->trace("Destroying Object");
#endif
    }

    void PathRuntime::recalculate
    ()
    {
        useDefinition();
    }

    bool
    PathRuntime::useDefinition
    ()
    {
        auto animDef = static_cast<PathDefinition*>(mDefinition);
#ifdef DREAM_LOG
        auto log = getLog();
        log->debug(
            "Loading {} spline with {} control points for {} ",
            animDef->getSplineType(),
            animDef->numberOfControlPoints(),
            getNameAndUuidString()
        );
#endif

        if (animDef->numberOfControlPoints() < 2)
        {
#ifdef DREAM_LOG
            log->warn("Skipping curve, not enough control points");
#endif
            mLoaded = true;
            return true;
        }

        mUStep = 1.0/(animDef->numberOfControlPoints()*animDef->getStepScalar());

        if (animDef->numberOfControlPoints() >= SPLINE_DIMENSIONS)
        {
            generate();
        }
#ifdef DREAM_LOG
        else
        {
            log->error("Not enough control points to generate spline");
        }
#endif

        mLoaded = true;
        return mLoaded;

    }

    void
    PathRuntime::generate
    ()
    {
#ifdef DREAM_LOG
        auto log = getLog();
#endif
        auto animDef = static_cast<PathDefinition*>(mDefinition);
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
            tsReal *result1 = nullptr, *result2 = nullptr, *result3 = nullptr;
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

#ifdef DREAM_LOG
                log->debug("Generating with u={}",u);
                log->debug("Got spline point ({},{},{})",result1[0], result1[1], result1[2]);
#endif

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

#ifdef DREAM_LOG
        log->debug("Finished Loading spline for {}",getNameAndUuidString());
#endif
    }

    vector<pair<vec3, vec3> > PathRuntime::getSplineDerivatives() const
    {
        return mSplineDerivatives;
    }

    bool PathRuntime::getWrapPath() const
    {
        return mWrapPath;
    }

    void PathRuntime::setWrapPath(bool wrapPath)
    {
        mWrapPath = wrapPath;
    }

    size_t PathRuntime::getCurrentIndex() const
    {
        return mCurrentIndex;
    }

    void PathRuntime::setCurrentIndex(size_t currentIndex)
    {
        mCurrentIndex = currentIndex;
    }

    Transform PathRuntime::stepPath()
    {
        Transform retval;

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

        mat4 mat(1.0f);
        mat  = glm::translate(mat,thisPoint);
        auto rot = mat4_cast(thisOrient);
        retval.setMatrix(mat*rot);
        vec3 ang = eulerAngles(thisOrient);
#ifdef DREAM_LOG
        auto log = getLog();
        log->trace("Got spline point {}/{} T({},{},{}) R({},{},{})",
            mCurrentIndex,mSplinePoints.size(),
            thisPoint.x, thisPoint.y, thisPoint.z,
            ang.x, ang.y, ang.z
        );
#endif
        return retval;

    }

    vector<vec3> PathRuntime::getSplinePoints() const
    {
        return mSplinePoints;
    }

    vector<glm::quat> PathRuntime::getSplineTangents() const
    {
       return mSplineTangents;
    }

    glm::vec3 PathRuntime::getSplinePoint(int index) const
    {
        if (index >=0 && index < mSplinePoints.size())
        {
            return mSplinePoints.at(index);
        }
        return vec3(0);
    }

    double PathRuntime::getUStep() const
    {
        return mUStep;
    }

    void PathRuntime::setUStep(double uStep)
    {
        mUStep = uStep;
    }

    quat PathRuntime::getHeading(vec3 point, vec3 t1, vec3 t2)
    {
        glm::mat4 mtx = glm::lookAt(t1,t2,vec3(0,1,0));
        quat q = quat(mtx);
        q.x = -q.x;
        q.y = -q.y;
        q.z = -q.z;

        return q;
    }

    const int PathRuntime::SPLINE_DIMENSIONS = 3;
    const int PathRuntime::SPLINE_DEGREES = 3;

}