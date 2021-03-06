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

#include "Event.h"

#include "Common/Logger.h"
#include "Entity/EntityRuntime.h"

namespace octronic::dream
{
    Event::Event
    (const map<string,string>& attributes)
        : mAttributes(attributes),
          mProcessed(false)
    {
        LOG_TRACE("Event: Creating");
    }

    Event::~Event()
    {
        LOG_TRACE("Event: Destroying");
    }

    void
    Event::setProcessed
    (bool p)
    {
        mProcessed = p;
    }

    bool
    Event::getProcessed
    ()
    const
    {
       return mProcessed;
    }

    string
    Event::getAttribute
    (const string &key) const
    {
        if (mAttributes.count(key) > 0)
        {
            return mAttributes.at(key);
        }
        return "";
    }

    void
    Event::setAttribute
    (const string &key, const string &value)
    {
        mAttributes[key] = value;
    }
}
