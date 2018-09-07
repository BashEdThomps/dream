/*
 * JSScriptInstance
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

#include "JSScriptInstance.h"
#include "../ScriptDefinition.h"

namespace Dream
{

    JSScriptInstance::JSScriptInstance
    (
        shared_ptr<ScriptDefinition> definition,
        shared_ptr<SceneObjectRuntime> transform
    )
        : ScriptInstance(definition,transform),
          mError(false)
    {
        setLogClassName("JSScriptInstance");
        auto log = getLog();
        log->trace( "Constructing {}", mDefinition->getNameAndUuidString() );
        return;
    }

    JSScriptInstance::~JSScriptInstance
    ()
    {
        auto log = getLog();
        log->trace("Destructing ", mDefinition->getNameAndUuidString() );
    }

    bool
    JSScriptInstance::load
    (string projectPath)
    {
        auto log = getLog();
        mAbsolutePath = projectPath + mDefinition->getAssetPath();
        log->info( "Script at {}" , mAbsolutePath );
        return mAbsolutePath.size() != 0;
    }

    void
    JSScriptInstance::update
    ()
    {

    }

    bool
    JSScriptInstance::getError
    ()
    {
        return mError;
    }

    void
    JSScriptInstance::setError
    (bool err)
    {
        mError = err;
    }


    void JSScriptInstance::loadExtraAttributes(nlohmann::json)
    {

    }

} // End of Dream
