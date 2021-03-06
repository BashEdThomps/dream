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
#include <map>

using std::string;
using std::map;

namespace octronic::dream
{
    class Event
    {
    private:
        map<string,string> mAttributes;
        volatile bool mProcessed;

    public:
        Event(const map<string,string>& attr);
        ~Event();

        string getAttribute(const string& key) const;

        void setAttribute(const string& key, const string& value);
        void setProcessed(bool p);
        bool getProcessed() const;
    };
}
