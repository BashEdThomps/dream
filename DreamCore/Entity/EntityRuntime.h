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

#include "EntityTasks.h"
#include "BoundingBox.h"
#include "Base/Runtime.h"
#include "Components/Graphics/Frustum.h"
#include "Math/Transform.h"

#include <vector>
#include <memory>

using std::vector;
using std::function;
using std::shared_ptr;
using nlohmann::json;

namespace octronic::dream
{
    class Event;
    class EntityDefinition;
    class SceneRuntime;

    class AssetDefinition;
    class AssetRuntime;

    class AnimationRuntime;
    class AnimationDefinition;

    class AudioDefinition;
    class AudioRuntime;

    class FontDefinition;
    class FontRuntime;

    class ModelDefinition;
    class ModelRuntime;

    class PathDefinition;
    class PathRuntime;

    class PhysicsObjectDefinition;
    class PhysicsObjectRuntime;

    class ScriptDefinition;
    class ScriptRuntime;

    class TextureDefinition;
    class TextureRuntime;

    class EntityRuntime : public Runtime
    {
    public:
        EntityRuntime(ProjectRuntime* pr, SceneRuntime* sceneRuntime, EntityDefinition* ed, bool randomUuid = false);
        ~EntityRuntime() override;

        void collectGarbage();

        SceneRuntime* getSceneRuntime() const;
        EntityDefinition* getEntityDefinition() const;

        bool createAssetRuntimes();
        bool createAnimationRuntime(AnimationDefinition*);
        bool createPathRuntime(PathDefinition*);
        bool createAudioRuntime(AudioDefinition*);
        bool createModelRuntime(ModelDefinition*);
        bool createScriptRuntime(ScriptDefinition*);
        bool createPhysicsObjectRuntime(PhysicsObjectDefinition*);
        bool createFontRuntime(FontDefinition*);
        bool createTextureRuntime(TextureDefinition*);

        FontRuntime* getFontRuntime() const;
        AnimationRuntime* getAnimationRuntime() const;
        PathRuntime*  getPathRuntime() const;
        AudioRuntime* getAudioRuntime() const;
        ModelRuntime* getModelRuntime() const;
        ScriptRuntime* getScriptRuntime() const;
        PhysicsObjectRuntime* getPhysicsObjectRuntime() const;
        AssetRuntime* getAssetRuntime(AssetType) const;
        TextureRuntime* getTextureRuntime() const;

        bool hasAnimationRuntime() const;
        bool hasPathRuntime() const;
        bool hasAudioRuntime() const;
        bool hasModelRuntime() const;
        bool hasScriptRuntime() const;
        bool hasPhysicsObjectRuntime() const;
        bool hasFontRuntime() const;
        bool hasTextureRuntime() const;

        Transform getTransform() const;
        Transform getInitialTransform() const;
        void setTransform(const Transform& transform);

        bool hasEvents() const;
        void addEvent(const Event& event);
        vector<Event>* getEventQueue();
        void clearEventQueue();

        EntityRuntime* getChildRuntimeByUuid(UuidType uuid);
        EntityRuntime* addChildFromTemplateUuid(UuidType uuid);
        int countAllChildren() const;
        size_t countChildren() const;
        void addChildRuntime(EntityRuntime*);
        void removeChildRuntime(EntityRuntime*);
        EntityRuntime* createAndAddChildRuntime(EntityDefinition*);
        vector<EntityRuntime*> getChildRuntimes();
        bool isChildOf(EntityRuntime*) const;

        void setScriptInitialised(bool i);
        bool getScriptInitialised() const;

        void setScriptError(bool i);
        bool getScriptError() const;

        bool isParentOf(EntityRuntime* child) const;
        void setParentEntityRuntime(EntityRuntime* parent);
        EntityRuntime* getParentEntityRuntime() const;

        bool loadFromDefinition() override;

        bool getDeleted() const;
        void setDeleted(bool deleted);

        void removeAnimationRuntime();
        void removeAudioRuntime();
        void removePathRuntime();
        void removeModelRuntime();
        void removeScriptRuntime();
        void removePhysicsObjectRuntime();
        void removeFontRuntime();
        void removeTextureRuntime();

        bool replaceAssetUuid(AssetType type, UuidType uuid);
        AssetDefinition* getAssetDefinitionByUuid(UuidType uuid);
        void setAssetDefinitionsMap(const map<AssetType, UuidType> &loadQueue);
        map<AssetType, UuidType> getAssetDefinitionsMap() const;

        BoundingBox getBoundingBox() const;
        void setBoundingBox(const BoundingBox& boundingBox);

        float distanceFrom(const EntityRuntime* other) const;
        float distanceFrom(const vec3& other) const;
        bool visibleInFrustum() const;
        bool containedInFrustum() const;
        bool containedInFrustumAfterTransform(const mat4& tx) const;
        bool exceedsFrustumPlaneAtTranslation(Frustum::Plane plane, const vec3& tx) const;

        bool applyToAll(const function<bool(EntityRuntime*)>& fn);
        EntityRuntime* applyToAll(const function<EntityRuntime*(EntityRuntime*)>& fn);
        void translateOffsetInitialWithChildren(const vec3& translation);
        void initTransform();

        bool loadChildrenFromDefinition(EntityDefinition* definition);

        shared_ptr<EntityScriptCreateStateTask> getScriptCreateStateTask() const;
        shared_ptr<EntityScriptOnInitTask> getScriptOnInitTask() const;
        shared_ptr<EntityScriptOnEventTask> getScriptOnEventTask() const;
        shared_ptr<EntityScriptOnUpdateTask> getScriptOnUpdateTask() const;

        string getAttribute(const string& key) const;
        void setAttribute(const string& key, const string& value);
        const map<string,string>& getAttributesMap() const;

        string getFontText() const;
        void setFontText(const string& fontText);

        vec4 getFontColor() const;
        void setFontColor(const vec4& fontColor);

        float getFontScale() const;
        void setFontScale(float fontScale);

        void pushTasks();
        bool allRuntimesLoaded() const;

    protected:
        ProjectRuntime* mProjectRuntimeHandle;
        SceneRuntime* mSceneRuntime;
        EntityRuntime* mParentEntityRuntime;
        vector<EntityRuntime*> mChildRuntimes;

        // Discrete Assets =====================================================
        AnimationRuntime* mAnimationRuntime;
        PathRuntime* mPathRuntime;
        PhysicsObjectRuntime* mPhysicsObjectRuntime;

        // Shared Runtimes =====================================================
        // Audio
        AudioRuntime* mAudioRuntime;

        // Font
        FontRuntime* mFontRuntime;
        string mFontText;
        vec4 mFontColor;
		float mFontScale;

        // Model
        ModelRuntime* mModelRuntime;

        // Script
        ScriptRuntime* mScriptRuntime;
        bool mScriptError;
        bool mScriptInitialised;
        shared_ptr<EntityScriptCreateStateTask> mScriptCreateStateTask;
        shared_ptr<EntityScriptOnInitTask> mScriptOnInitTask;
        shared_ptr<EntityScriptOnUpdateTask> mScriptOnUpdateTask;
        shared_ptr<EntityScriptOnEventTask> mScriptOnEventTask;
        shared_ptr<EntityScriptRemoveStateTask> mScriptRemoveStateTask;

        // Sprite Texture
        TextureRuntime* mTextureRuntime;

        // Transform
        Transform mInitialTransform;
        Transform mCurrentTransform;
        BoundingBox mBoundingBox;

        // Flags
        bool mDeleted;
        bool mRandomUuid;
        map<string,string> mAttributes;
        vector<Event> mEventQueue;
        map<AssetType,UuidType> mAssetDefinitions;
    };
}
