/*
* GraphicsComponent
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

#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include "../../Constants.h"
#include "../../GameController.h"
// Dream
#include "../ComponentInterface.h"
#include "AssimpModelInstance.h"
#include "ShaderInstance.h"
#include "Camera.h"

// STD LIB
#include <iostream>
#include <map>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>

#define Graphics_INTERFACE_DEFAULT_SCREEN_WIDTH 1280
#define Graphics_INTERFACE_DEFAULT_SCREEN_HEIGHT 720

#define CLEAR_RED   0
#define CLEAR_GREEN 1
#define CLEAR_BLUE  2
#define CLEAR_ALPHA 3

namespace Dream {
  using namespace std;
  class GraphicsComponent : public ComponentInterface {
  private:
      glm::mat4 mProjectionMatrix;
      glm::mat4 mViewMatrix;
      GLfloat mSpriteVertices[24] = {
          // Pos      // Tex
          0.0f, 1.0f, 0.0f, 1.0f,
          1.0f, 0.0f, 1.0f, 0.0f,
          0.0f, 0.0f, 0.0f, 0.0f,
          0.0f, 1.0f, 0.0f, 1.0f,
          1.0f, 1.0f, 1.0f, 1.0f,
          1.0f, 0.0f, 1.0f, 0.0f
      };
      GLuint mSpriteVBO;
      GLuint mSpriteQuadVAO;
      int mWindowWidth;
      int mWindowHeight;
      string mScreenName;
      bool mWindowShouldClose;
      SDL_Window *mWindow;
      Camera *mCamera;
      float mMinimumDraw = 0.1f;
      float mMaximumDraw = 1000.0f;
      SDL_GLContext mContext;
      vector<SDL_Event> mEvents;
      vector<SceneObject*> m2DQueue;
      vector<SceneObject*> m3DQueue;
      vector<LightInstance*> mLightQueue;
      glm::mat4 mOrthoProjection;
      vector<float> mClearColour;
      vector<float> mAmbientLightColour;
      GameController *mGameController;
  public:
      void setWindowWidth(int);
      void setWindowHeight(int);
      int getWindowWidth();
      int getWindowHeight();

      void setScreenName(string);
      string getScreenName();

      void closeWindow();

      void clear2DQueue();
      void addTo2DQueue(SceneObject*);
      void draw2DQueue();

      void addToLightQueue(LightInstance*);
      void clearLightQueue();

      void clear3DQueue();
      void addTo3DQueue(SceneObject*);
      void draw3DQueue();

      GraphicsComponent(Camera*);
      ~GraphicsComponent(void);
      bool createSDLWindow();

      bool init(void);
      void update(Scene*);
      void drawSprite(SceneObject*);
      void drawFont(SceneObject*);
      void drawModel(SceneObject*);
      bool checkGLError(string);
      bool isWindowShouldCloseFlagSet();
      SDL_Window* getWindow();
      vector<SDL_Event> getSDL_Events();

      void setClearColour(vector<float>);
      void setAmbientLightColour(vector<float>);

      void create2DVertexObjects();
      void setWindowShouldClose(bool);
      glm::mat4 getViewMatrix();
      glm::mat4 getProjectionMatrix();
      void swapBuffers();
      void setGameController(GameController* gameController);
      GameController *getGameController();
  private:
      void updateWindowDimensions();

  }; // End of GraphicsComponent

} // End of Dream
#endif // End of GRAPHICSCOMPONENT_H
