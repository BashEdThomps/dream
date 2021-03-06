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
#include "FontDefinition.h"



namespace octronic::dream
{
    FontDefinition::FontDefinition
    (ProjectDefinition* pd, const json &js)
        :AssetDefinition("FontDefinition",pd,js)
    {
    }

    void FontDefinition::setSize(unsigned int size)
    {
        mJson[Constants::ASSET_ATTR_FONT_SIZE] = size;
    }

    unsigned int FontDefinition::getSize()
    {
        unsigned int size = 1;
        if (mJson.find(Constants::ASSET_ATTR_FONT_SIZE) == mJson.end())
        {
            mJson[Constants::ASSET_ATTR_FONT_SIZE] = size;
        }
        size = mJson[Constants::ASSET_ATTR_FONT_SIZE];
        return size;
    }
}

