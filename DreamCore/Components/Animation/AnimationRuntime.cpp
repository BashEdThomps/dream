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

#include "AnimationRuntime.h"
#include "../Time.h"
#include "../../Scene/SceneObject/SceneObjectRuntime.h"
#include "../../Scene/SceneRuntime.h"
#include "../../Project/ProjectRuntime.h"
#include "../../Utilities/String.h"
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "AnimationEasing.h"

namespace Dream
{

    AnimationRuntime::AnimationRuntime
    (
        AnimationDefinition* definition,
        SceneObjectRuntime* runtime
    ) : DiscreteAssetRuntime(definition,runtime),
        mCurrentTime(0.0),
        mDuration(1.0),
        mLooping(false),
        mRunning(false)
    {
#ifdef DREAM_DEBUG
        setLogClassName("AnimationRuntime");
        auto log = getLog();
        log->trace("Constructing Object");
#endif
    }

    AnimationRuntime::~AnimationRuntime
    ()
    {

#ifdef DREAM_DEBUG
        auto log = getLog();
        log->trace("Destroying Object");
#endif
    }

    bool
    AnimationRuntime::useDefinition
    ()
    {
        auto animDef = static_cast<AnimationDefinition*>(mDefinition);
        mDuration = animDef->getDuration();
        mLooping = animDef->getLooping();
        mKeyframes = animDef->getKeyframes();
        createTweens();
        mLoaded = true;
        return mLoaded;
    }

    void
    AnimationRuntime::stepAnimation
    (double deltaTime)
    {
        // x1000 to get seconds to ms

#ifdef DREAM_DEBUG
        auto log = getLog();
#endif
        auto timeInMs = static_cast<unsigned int>((deltaTime*1000));
        if (mRunning)
        {

#ifdef DREAM_DEBUG
            log->error("Delta Time {} | mCurrentTime {}",deltaTime,mCurrentTime);
#endif
            if (mLooping)
            {
                mCurrentTime = (mCurrentTime + timeInMs) % mDuration;
            }
            else
            {
                mCurrentTime += timeInMs;
            }
            seekAll(mCurrentTime);
        }
    }

    unsigned int
    AnimationRuntime::getCurrentTime
    ()
    const
    {
        return mCurrentTime;
    }

    void
    AnimationRuntime::setCurrentTime
    (unsigned int currentTime)
    {
        mCurrentTime = currentTime;
    }

    unsigned int
    AnimationRuntime::getDuration
    ()
    const
    {
        return mDuration;
    }

    void
    AnimationRuntime::setDuration
    (unsigned int duration)
    {
        mDuration = duration;
    }

    bool
    AnimationRuntime::getLooping
    ()
    const
    {
        return mLooping;
    }

    void
    AnimationRuntime::setLooping
    (bool looping)
    {
        mLooping = looping;
    }

    bool
    AnimationRuntime::getRunning
    ()
    const
    {
        return mRunning;
    }

    void
    AnimationRuntime::setRunning
    (bool running)
    {
        mRunning = running;
    }

    void
    AnimationRuntime::createTweens
    ()
    {
        orderByTime();
        int numKeyframes = mKeyframes.size();
        for (int i=0; i < numKeyframes; i++)
        {
            vec3 tx = mKeyframes.at(i).getTranslation();
            vec3 rx = mKeyframes.at(i).getRotation();
            vec3 sx = mKeyframes.at(i).getScale();
            AnimationEasing::Type easing = mKeyframes.at(i).getEasingType();

            if (i==0)
            {
                mTweenTranslationX = tweeny::from(tx.x);
                mTweenTranslationY = tweeny::from(tx.y);
                mTweenTranslationZ = tweeny::from(tx.z);

                mTweenRotationX = tweeny::from(rx.x);
                mTweenRotationY = tweeny::from(rx.y);
                mTweenRotationZ = tweeny::from(rx.z);

                mTweenScaleX = tweeny::from(sx.x);
                mTweenScaleY = tweeny::from(sx.y);
                mTweenScaleZ = tweeny::from(sx.z);
            }
            else
            {
                auto lastFrameTime = mKeyframes.at(i-1).getTime();
                auto thisFrameTime = mKeyframes.at(i).getTime();
                unsigned int duringTime = thisFrameTime-lastFrameTime;

                mTweenTranslationX.to(tx.x).during(duringTime);
                applyEasing(mTweenTranslationX,easing);
                mTweenTranslationY.to(tx.y).during(duringTime);
                applyEasing(mTweenTranslationY,easing);
                mTweenTranslationZ.to(tx.z).during(duringTime);
                applyEasing(mTweenTranslationZ,easing);

                mTweenRotationX.to(rx.x).during(duringTime);
                applyEasing(mTweenRotationX,easing);
                mTweenRotationY.to(rx.y).during(duringTime);
                applyEasing(mTweenRotationY,easing);
                mTweenRotationZ.to(rx.z).during(duringTime);
                applyEasing(mTweenRotationZ,easing);

                mTweenScaleX.to(sx.x).during(duringTime);
                applyEasing(mTweenScaleX,easing);
                mTweenScaleY.to(sx.y).during(duringTime);
                applyEasing(mTweenScaleY,easing);
                mTweenScaleZ.to(sx.z).during(duringTime);
                applyEasing(mTweenScaleZ,easing);
            }
        }

        if (mLooping)
        {
            vec3 tx = mKeyframes.at(0).getTranslation();
            vec3 rx = mKeyframes.at(0).getRotation();
            vec3 sx = mKeyframes.at(0).getScale();

            auto lastIndex = mKeyframes.size()-1;
            auto duringTime = mDuration - mKeyframes.at(lastIndex).getTime();
            AnimationEasing::Type easing = mKeyframes.at(lastIndex).getEasingType();

            mTweenTranslationX.to(tx.x).during(duringTime);
            applyEasing(mTweenTranslationX,easing);
            mTweenTranslationY.to(tx.y).during(duringTime);
            applyEasing(mTweenTranslationY,easing);
            mTweenTranslationZ.to(tx.z).during(duringTime);
            applyEasing(mTweenTranslationZ,easing);

            mTweenRotationX.to(rx.x).during(duringTime);
            applyEasing(mTweenRotationX,easing);
            mTweenRotationY.to(rx.y).during(duringTime);
            applyEasing(mTweenRotationY,easing);
            mTweenRotationZ.to(rx.z).during(duringTime);
            applyEasing(mTweenRotationZ,easing);

            mTweenScaleX.to(sx.x).during(duringTime);
            applyEasing(mTweenScaleX,easing);
            mTweenScaleY.to(sx.y).during(duringTime);
            applyEasing(mTweenScaleY,easing);
            mTweenScaleZ.to(sx.z).during(duringTime);
            applyEasing(mTweenScaleZ,easing);
        }
    }

    void
    AnimationRuntime::run
    ()
    {
        mRunning = true;
    }

    void
    AnimationRuntime::pause
    ()
    {
        mRunning = !mRunning;
    }

    void
    AnimationRuntime::reset
    ()
    {
        mCurrentTime = 0;
        seekAll(0);
    }

    void
    AnimationRuntime::seekAll
    (unsigned int pos)
    {
#ifdef DREAM_DEBUG
        auto log = getLog();
        log->trace("Seeing to {}",pos);
#endif
        vec3 newTx, newRx, newSx;
        newTx.x = mTweenTranslationX.seek(pos);
        newTx.y = mTweenTranslationY.seek(pos);
        newTx.z = mTweenTranslationZ.seek(pos);

        newRx.x = mTweenRotationX.seek(pos);
        newRx.y = mTweenRotationY.seek(pos);
        newRx.z = mTweenRotationZ.seek(pos);

        newSx.x = mTweenScaleX.seek(pos);
        newSx.y = mTweenScaleY.seek(pos);
        newSx.z = mTweenScaleZ.seek(pos);

        mat4 matrix = mat4(1.0f);
        matrix = glm::translate(matrix,newTx);
        matrix = matrix*mat4_cast(quat(newRx));
        matrix = glm::scale(matrix,newSx);
        mSceneObjectRuntime->getTransform().setMatrix(matrix);

    }

    void
    AnimationRuntime::orderByTime
    ()
    {
        std::sort(mKeyframes.begin(),mKeyframes.end());
    }

    void
    AnimationRuntime::applyEasing
    (tweeny::tween<float>& twn, AnimationEasing::Type easing)
    {
        switch(easing)
        {
            case AnimationEasing::Type::EasingLinear:
                twn.via(tweeny::easing::linear);
                break;

            case AnimationEasing::Type::EasingQuadraticIn:
                twn.via(tweeny::easing::quadraticIn);
                break;
            case AnimationEasing::Type::EasingQuadraticOut:
                twn.via(tweeny::easing::quadraticOut);
                break;
            case AnimationEasing::Type::EasingQuadraticInOut:
                twn.via(tweeny::easing::quadraticInOut);
                break;

            case AnimationEasing::Type::EasingCubicIn:
                twn.via(tweeny::easing::cubicIn);
                break;
            case AnimationEasing::Type::EasingCubicOut:
                twn.via(tweeny::easing::cubicOut);
                break;
            case AnimationEasing::Type::EasingCubicInOut:
                twn.via(tweeny::easing::cubicInOut);
                break;

            case AnimationEasing::Type::EasingQuarticIn:
                twn.via(tweeny::easing::quarticIn);
                break;
            case AnimationEasing::Type::EasingQuarticOut:
                twn.via(tweeny::easing::quarticOut);
                break;
            case AnimationEasing::Type::EasingQuarticInOut:
                twn.via(tweeny::easing::quarticInOut);
                break;

            case AnimationEasing::Type::EasingQuinticIn:
                twn.via(tweeny::easing::quinticIn);
                break;
            case AnimationEasing::Type::EasingQuinticOut:
                twn.via(tweeny::easing::quinticOut);
                break;
            case AnimationEasing::Type::EasingQuinticInOut:
                twn.via(tweeny::easing::quinticInOut);
                break;

            case AnimationEasing::Type::EasingSinusoidalIn:
                twn.via(tweeny::easing::sinusoidalIn);
                break;
            case AnimationEasing::Type::EasingSinusoidalOut:
                twn.via(tweeny::easing::sinusoidalOut);
                break;
            case AnimationEasing::Type::EasingSinusoidalInOut:
                twn.via(tweeny::easing::sinusoidalInOut);
                break;

            case AnimationEasing::Type::EasingExponentialIn:
                twn.via(tweeny::easing::exponentialIn);
                break;
            case AnimationEasing::Type::EasingExponentialOut:
                twn.via(tweeny::easing::exponentialOut);
                break;
            case AnimationEasing::Type::EasingExponentialInOut:
                twn.via(tweeny::easing::exponentialInOut);
                break;

            case AnimationEasing::Type::EasingCircularIn:
                twn.via(tweeny::easing::circularIn);
                break;
            case AnimationEasing::Type::EasingCircularOut:
                twn.via(tweeny::easing::circularOut);
                break;
            case AnimationEasing::Type::EasingCircularInOut:
                twn.via(tweeny::easing::circularInOut);
                break;

            case AnimationEasing::Type::EasingBounceIn:
                twn.via(tweeny::easing::bounceIn);
                break;
            case AnimationEasing::Type::EasingBounceOut:
                twn.via(tweeny::easing::bounceOut);
                break;
            case AnimationEasing::Type::EasingBounceInOut:
                twn.via(tweeny::easing::bounceInOut);
                break;

            case AnimationEasing::Type::EasingElasticIn:
                twn.via(tweeny::easing::elasticIn);
                break;
            case AnimationEasing::Type::EasingElasticOut:
                twn.via(tweeny::easing::elasticOut);
                break;
            case AnimationEasing::Type::EasingElasticInOut:
                twn.via(tweeny::easing::elasticInOut);
                break;

            case AnimationEasing::Type::EasingBackIn:
                twn.via(tweeny::easing::backIn);
                break;
            case AnimationEasing::Type::EasingBackOut:
                twn.via(tweeny::easing::backOut);
                break;
            case AnimationEasing::Type::EasingBackInOut:
                twn.via(tweeny::easing::backInOut);
                break;
        }
    }
}