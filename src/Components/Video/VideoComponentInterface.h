/*
* VideoInterface
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

#ifndef VIDEOINTERFACE_H
#define VIDEOINTERFACE_H

#include <iostream>
#include "../ComponentInterface.h"

#define VIDEO_INTERFACE_DEFAULT_SCREEN_WIDTH  1280
#define VIDEO_INTERFACE_DEFAULT_SCREEN_HEIGHT 720

namespace Dream   {
  namespace Components {
    namespace Video   {
      class VideoComponentInterface : public Dream::Components::ComponentInterface {
      protected:
        int mScreenWidth;
        int mScreenHeight;
        std::string mScreenName;
        bool mWindowShouldClose;
      public:
        VideoComponentInterface(void);
        virtual ~VideoComponentInterface(void) {};
        void setScreenWidth(int);
        int  getScreenWidth();
        void setScreenHeight(int);
        int  getScreenHeight();
        void setScreenName(std::string);
        std::string getScreenName();
        void setupWindowEventHandlers();
        bool isWindowShouldCloseFlagSet();

        virtual void closeWindow() = 0;
        virtual void setCursorEnabled(bool) = 0;
      }; // End of VideoInterface

    } // End of Video
  } // End of Components
} // End of Dream

#endif // End of VIDEOINTERFACE_H
