#include "CacheContentWindow.h"
#include "DreamToolContext.h"
#include <DreamCore.h>

namespace octronic::dream::tool
{
    CacheContentWindow::CacheContentWindow
    (DreamToolContext* proj) : ImGuiWidget(proj,false)
    {
    }

    CacheContentWindow::~CacheContentWindow
    ()
    {

    }

    void
    CacheContentWindow::draw
    ()
    {
        ImGui::Begin("Cache Content");

        if (mContext->getProject())
        {
            auto projRunt = mContext->getProject()->getRuntime();
            if (projRunt)
            {
                char title[128] = {0};
                string formatStr = "%s Cache (%d)";

                auto audioCache = projRunt->getAudioCache();
                snprintf(title, 128, formatStr.c_str(), "Audio", audioCache->runtimeCount());
                if (ImGui::CollapsingHeader(title))
                {
                    for (auto& instance : *audioCache->getRuntimeVectorHandle())
                    {
                        ImGui::Text("%s",instance->getNameAndUuidString().c_str());
                    }
                }

				auto fontCache = projRunt->getFontCache();
                snprintf(title, 128, formatStr.c_str(), "Font", fontCache->runtimeCount());

                if (ImGui::CollapsingHeader(title))
                {
                    for (auto& instance : *fontCache->getRuntimeVectorHandle())
                    {
                        ImGui::Text("%s",instance->getNameAndUuidString().c_str());
                    }
                }

                auto materialCache = projRunt->getMaterialCache();
                snprintf(title, 128, formatStr.c_str(), "Material", materialCache->runtimeCount());
                if (ImGui::CollapsingHeader(title))
                {
                    for (auto& instance : *materialCache->getRuntimeVectorHandle())
                    {
                        ImGui::Text("%s",instance->getNameAndUuidString().c_str());
                    }
                }

                auto modelCache = projRunt->getModelCache();
                snprintf(title, 128, formatStr.c_str(), "Model", modelCache->runtimeCount());
                if (ImGui::CollapsingHeader(title))
                {
                    for (auto& instance : *modelCache->getRuntimeVectorHandle())
                    {
                        ImGui::Text("%s",instance->getNameAndUuidString().c_str());
                    }
                }

                auto scriptCache = projRunt->getScriptCache();
                snprintf(title, 128, formatStr.c_str(), "Script", scriptCache->runtimeCount());
                if (ImGui::CollapsingHeader(title))
                {
                    for (auto& instance : *scriptCache->getRuntimeVectorHandle())
                    {
                        ImGui::Text("%s",instance->getNameAndUuidString().c_str());
                    }
                }

                auto shaderCache = projRunt->getShaderCache();
                snprintf(title, 128, formatStr.c_str(), "Shader", shaderCache->runtimeCount());
                if (ImGui::CollapsingHeader(title))
                {
                    for (auto& instance : *shaderCache->getRuntimeVectorHandle())
                    {
                        ImGui::Text("%s",instance->getNameAndUuidString().c_str());
                    }
                }

                auto textureCache = projRunt->getTextureCache();
                snprintf(title, 128, formatStr.c_str(), "Texture", textureCache->runtimeCount());
                if (ImGui::CollapsingHeader(title))
                {
                    for (auto& instance : *textureCache->getRuntimeVectorHandle())
                    {
                        ImGui::Text("%s",instance->getNameAndUuidString().c_str());
                    }
                }
            }
        }
        ImGui::End();
    }
}
