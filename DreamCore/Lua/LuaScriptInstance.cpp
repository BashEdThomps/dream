/*
 * LuaScriptInstance
 *
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

#include "LuaScriptInstance.h"

#include "ScriptDefinition.h"

namespace Dream
{

    LuaScriptInstance::LuaScriptInstance
    (ScriptDefinition* definition, SceneObjectRuntime* transform)
        : IAssetInstance(definition,transform),
        mError(false)
    {
        if (Constants::DEBUG)
        {
            cout << "LuaScriptInstance: Constructing "
                 << mDefinitionHandle->getNameAndUuidString() << endl;
        }
        return;
    }

    LuaScriptInstance::~LuaScriptInstance
    ()
    {
        if (Constants::DEBUG)
        {
            cout << "LuaScriptInstance: Destructing "
                 << mDefinitionHandle->getNameAndUuidString() << endl;
        }
    }

    bool
    LuaScriptInstance::load
    (string projectPath)
    {
        mAbsolutePath = projectPath + mDefinitionHandle->getAssetPath();
        if (Constants::DEBUG)
        {
            cout << "LuaScriptInstance: Script at " << mAbsolutePath << endl;
        }
        return mAbsolutePath.size() != 0;
    }

    void
    LuaScriptInstance::update
    ()
    {

    }

    bool
    LuaScriptInstance::getError
    ()
    {
        return mError;
    }

    void
    LuaScriptInstance::setError
    (bool err)
    {
        mError = err;
    }


    void LuaScriptInstance::loadExtraAttributes(nlohmann::json)
    {

    }

} // End of Dream
