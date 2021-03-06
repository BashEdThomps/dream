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

#include "Base/Definition.h"

using std::string;
using std::vector;

namespace octronic::dream
{
    class Project;
    class SceneDefinition;
    class AssetDefinition;

    class ProjectDefinition : public Definition
    {

    public:
        ProjectDefinition(const json& data);
        ~ProjectDefinition() override;

        UuidType getStartupSceneUuid();
        void setStartupSceneUuid(UuidType sceneUuid);
        SceneDefinition* getStartupSceneDefinition();

        void loadChildDefinitions();

        size_t countAssetDefinitions();
        AssetDefinition* getAssetDefinitionByUuid(UuidType uuid);
        AssetDefinition* getAssetDefinitionByName(const string& name);
        void addAssetDefinition(AssetDefinition* def);

        size_t countScenesDefinitions();
        SceneDefinition* getSceneDefinitionByUuid(UuidType uuid);
        SceneDefinition* getSceneDefinitionByName(const string& name);
        vector<SceneDefinition*> getSceneDefinitionsVector();
        void removeSceneDefinition(SceneDefinition* sceneDef);

        void removeAssetDefinition(AssetDefinition* assetDef);
        vector<AssetDefinition*> getAssetDefinitionsVector();
        vector<AssetDefinition*> getAssetDefinitionsVector(AssetType type);
        SceneDefinition* createNewSceneDefinition();
        AssetDefinition* createNewAssetDefinition(AssetType type);
        map<AssetType,vector<AssetDefinition*> > getAssetDefinitionsMap();

        json toJson() override;

        void deleteAssetDefinitions();
        void deleteSceneDefinitions();

        long getSceneDefinitionIndex(SceneDefinition*);
        SceneDefinition* getSceneDefinitionAtIndex(int index);
        long getAssetDefinitionIndex(AssetType, AssetDefinition*);
        long getAssetDefinitionIndex(AssetType, UuidType);
        AssetDefinition* getAssetDefinitionAtIndex(AssetType, int);

        vector<string> getAssetNamesVector(AssetType);

        map<AssetType, vector<string> >& getAssetDefinitionGroups();
        void regroupAssetDefinitions();

    public: // static
        static ProjectDefinition* createNewProjectDefinition(const string& name = Constants::PROJECT_DEFAULT_NAME);

    private:
        void loadSceneDefinitions();
        void loadAssetDefinitions();
        void loadSingleAssetDefinition(const json& assetDefinition);
        void loadSingleSceneDefinition(const json& sceneDefinition);
        AssetDefinition* createAssetDefinition(const json& assetDefinitionJs);
    private:
        map<AssetType,vector<string> > mAssetDefinitionGroups;
        vector<SceneDefinition*> mSceneDefinitions;
        vector<AssetDefinition*> mAssetDefinitions;
    };
}
