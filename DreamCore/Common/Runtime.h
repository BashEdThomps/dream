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

#include "DreamObject.h"
#include "Definition.h"

using std::string;

namespace Dream
{
    class Definition;

    /**
     * @brief Abstract class that contains Runtime data for DreamObjects that
     * are used to implement a Project.
     */
    class Runtime : public DreamObject
    {
    protected:
        /**
         * @brief Definition from which this runtime was instanciated.
         */
        Definition* mDefinition;
        /**
         * @brief UUID of this Runtime, given by it's Definition.
         */
        string mUuid;
        /**
         * @brief Name of this Runtime, given by it's Definition.
         */
        string mName;
    public:
        /**
         * @brief Default Constructor
         * @param def Definition from which the Runtime was instanciated.
         */
        Runtime
        (Definition* def)
            : DreamObject("Runtime"),
              mDefinition(def),
              mUuid(def->getUuid()),
              mName(def->getName()) {}

        /**
         * @brief Default destructor.
         */
        virtual
        ~Runtime
        ()
        {

        }

        /**
         * @return The Runtime's UUID - same as it's Definition.
         */
        inline string
        getUuid
        ()
        const
        {
            return mUuid;
        }

        inline void
        setUuid
        (const string& uuid)
        {
            mUuid = uuid;
        }

        inline bool
        hasUuid
        (string uuid)
        const
        {
            return getUuid().compare(uuid) == 0;
        }

        /**
         * @return The Runtime's Name - same as it's Definition.
         */
        inline string
        getName
        ()
        const
        {
            return mName;
        }

        inline void
        setName
        (const string& name)
        {
            mName = name;
        }

        inline bool
        hasName
        (const string& name)
        const
        {
            return getName().compare(name) == 0;
        }

        inline string
        getNameAndUuidString
        ()
        const
        {
            return "[" + getName() + " : " + getUuid() + "]";
        }

        /**
         * @brief Use information from the give Definition to create the Runtime
         * object's initial state.
         * @return Success/Failure.
         */
        virtual bool useDefinition() = 0;

        /**
         * @brief Delete anything managed by this runtime that was instanciated
         * but no longer needed .
         */
        virtual void collectGarbage() = 0;

        /**
         * @return The Definition from which this Runtime was Instanciated.
         */
        inline Definition*
        getDefinition
        ()
        {
            return mDefinition;
        }
    };
}