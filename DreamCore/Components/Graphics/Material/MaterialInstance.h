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


#pragma once

#include <assimp/types.h>
#include <vector>
#include <memory>
#include "../../IAssetInstance.h"
#include <glm/vec3.hpp>

using namespace std;
using namespace glm;

namespace Dream
{
    struct RGB;
    class ModelMesh;
    class ShaderInstance;
    class MaterialDefinition;
	class TextureInstance;

    class MaterialInstance : public IAssetInstance
    {
    public:
        MaterialInstance(MaterialDefinition* def, SceneObjectRuntime* rt);
        ~MaterialInstance() override;

        void addMesh(ModelMesh* mesh);
        void clearMeshes();

        bool operator==(MaterialInstance& other);
        void debug();
        void logMeshes();
        void draw();

        bool load(string) override;
        void loadExtraAttributes(nlohmann::json) override;

        TextureInstance* getDiffuseTexture() const;
        void setDiffuseTexture(TextureInstance* diffuseTexture);

        TextureInstance* getSpecularTexture() const;
        void setSpecularTexture(TextureInstance* specularTexture);

        TextureInstance* getNormalTexture() const;
        void setNormalTexture(TextureInstance* normalTexture);

        TextureInstance* getDisplacementTexture() const;
        void setDisplacementTexture(TextureInstance* displacementTexture);

        ShaderInstance* getShader() const;
        void setShader(ShaderInstance* shader);

        aiColor4D getColorDiffuse() const;
        void setColorDiffuse(aiColor4D colorDiffuse);

        aiColor4D getColorAmbient() const;
        void setColorAmbient(aiColor4D colorAmbient);

        aiColor4D getColorSpecular() const;
        void setColorSpecular(aiColor4D colorSpecular);

        aiColor4D getColorEmissive() const;
        void setColorEmissive(aiColor4D colorEmissive);

        aiColor4D getColorReflective() const;
        void setColorReflective(aiColor4D colorReflective);

        ai_real getShininessStrength() const;
        void setShininessStrength(ai_real shininessStrength);

    protected:
        ai_real mOpacity = 0.0f;
        ai_real mBumpScaling = 0.0f;
        ai_real mHardness = 0.0f;
        ai_real mReflectivity = 0.0f;
        ai_real mShininessStrength = 0.0f;
        ai_real mRefracti = 0.0f;

        aiColor4D mColorDiffuse;
        aiColor4D mColorAmbient;
        aiColor4D mColorSpecular;
        aiColor4D mColorEmissive;
        aiColor4D mColorReflective;

        TextureInstance* mDiffuseTexture;
        TextureInstance* mSpecularTexture;
        TextureInstance* mNormalTexture;
        TextureInstance* mDisplacementTexture;
        ShaderInstance*  mShader;

        vector<ModelMesh*> mUsedBy;

        aiColor4D rgbToAiColor4D(RGB color);
    };
}
