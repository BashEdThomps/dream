/*
 * This file may be distributed under the terms of GNU Public License version
 * 3 (GPL v3) as defined by the Free Software Foundation (FSF). A copy of the
 * license should have been included with this file, or the project in which
 * this file belongs to. You may also find the details of GPL v3 at:
 * http://www.gnu.org/licenses/gpl-3.0.txt
 *
 * If you have any questions regarding the use of this file, feel free to
 * contact the author of this file, or the owner of the project in which
 * this file belongs to.
 */

#pragma once

#include <string>
#include <vector>

#include "SceneState.h"

#include "../Common/Runtime.h"
#include "../Components/Transform.h"
#include "../Components/Graphics/Camera.h"

using std::string;
using std::vector;
using std::shared_ptr;

namespace Dream
{
    class ProjectRuntime;
    class SceneObject;
    class SceneDefinition;
    class AssetRuntime;
    class AssetDefinition;
    class SceneObjectRuntime;
    class ShaderRuntime;
    class ScriptRuntime;

    class SceneRuntime : public Runtime
    {
    private:
        SceneState mState;
        vector<float> mClearColour;
        vector<float> mAmbientColour;
        ProjectRuntime* mProjectRuntime;
        vector<SceneObjectRuntime*> mSceneObjectRuntimeCleanUpQueue;
        SceneObjectRuntime* mRootSceneObjectRuntime;
        ShaderRuntime* mLightingPassShader;
        ShaderRuntime* mShadowPassShader;
        ScriptRuntime* mInputScript;
        ScriptRuntime* mNanoVGScript;
        Camera mCamera;
        float mMinDrawDistance;
        float mMaxDrawDistance;
        float mMeshCullDistance;

    public:
        SceneRuntime(SceneDefinition* sd, ProjectRuntime* parent);
        ~SceneRuntime() override;

        Camera* getCamera();
        SceneState getState();
        void setState(SceneState state);

        const vector<float> getGravity();
        void setGravity(const vector<float>& gravity);

        const vector<float>& getClearColour();
        void setClearColour(const vector<float>& clearColour);

        const vector<float>& getAmbientColour();
        void setAmbientColour(const vector<float>& ambientColour);

        const vector<SceneObjectRuntime*> getSceneObjectRuntimeCleanUpQueue();
        void addSceneObjectRuntimeToCleanUpQueue(SceneObjectRuntime*);
        void clearSceneObjectRuntimeCleanUpQueue();
        void processSceneObjectRuntimeCleanUpQueue();

        void createAllAssetRuntimes();

        bool useDefinition() override;
        void destroyRuntime();

        void setDeleteFlagOnAllSceneObjectRuntimes();

        bool hasRootSceneObjectRuntime();
        void setRootSceneObjectRuntime(SceneObjectRuntime* sceneObject);
        SceneObjectRuntime* getRootSceneObjectRuntime();

        SceneObjectRuntime* getSceneObjectRuntimeByName(const string& name);
        SceneObjectRuntime* getSceneObjectRuntimeByUuid(uint32_t uuid);

        int countSceneObjectRuntimes();
        int countChildrenOfSceneObjectRuntime(SceneObjectRuntime*);

        ProjectRuntime* getProjectRuntime();

        void showScenegraph();

        void collectGarbage() override;

        void setAssetDefinitionUuidLoadQueue(const vector<string>& loadQueue);

        bool getPhysicsDebug();
        void setPhysicsDebug(bool physicsDebug);

        ShaderRuntime* getLightingPassShader() const;
        void setLightingPassShader(ShaderRuntime* lightingShader);

        ShaderRuntime* getShadowPassShader() const;
        void setShadowPassShader(ShaderRuntime* shadowPassShader);

        void setMeshCullDistance(float);
        float getMeshCullDistance() const;

        float getMinDrawDistance() const;
        void setMinDrawDistance(float);

        float getMaxDrawDistance() const;
        void setMaxDrawDistance(float);


        vector<AssetRuntime*> getAssetRuntimes(AssetType) const;
        vector<SceneObjectRuntime*> getSceneObjectsWithRuntimeOf(AssetDefinition* def) const;

        ScriptRuntime* getInputScript() const;
        ScriptRuntime* getNanoVGScript() const;

        /**
         * @return Gets the nearest SceneObject to the Camera's position excluding
         * the SceneObject the Camera is focused on.
         */
        SceneObjectRuntime* getNearestToCamera();
    };
}
