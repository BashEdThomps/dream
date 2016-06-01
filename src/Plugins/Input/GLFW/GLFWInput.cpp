//
//  GLFWInput.cpp
//  Dream
//
//  Created by Ashley Thompson on 16/05/2016.
//  Copyright © 2016 Octronic. All rights reserved.
//

#include "GLFWInput.h"

namespace Dream   {
namespace Plugins {
namespace Input   {
namespace GLFW    {
	
	void onKeyboardEvent(GLFWwindow* window, int key, int scancode, int action, int mods) {
		InputEvent keyboardEvent(INPUT_TYPE_KEYBOARD);
		keyboardEvent.setKey(key);
		keyboardEvent.setScancode(scancode);
		keyboardEvent.setAction(action);
		keyboardEvent.setMods(mods);
		InputPluginInterface::pushEvent(keyboardEvent);
	}
	
	void onMouseButtonEvent(GLFWwindow* window, int button, int action, int mods) {
		InputEvent mouseEvent(INPUT_TYPE_MOUSE_BUTTON);
		mouseEvent.setButton(button);
		mouseEvent.setAction(action);
		mouseEvent.setMods(mods);
		InputPluginInterface::pushEvent(mouseEvent);
	}
	
	void onMouseScrollEvent(GLFWwindow* window, double xoffset, double yoffset) {
		InputEvent mouseEvent(INPUT_TYPE_MOUSE_SCROLL);
		mouseEvent.setXScrollOffset(xoffset);
		mouseEvent.setYScrollOffset(yoffset);
		InputPluginInterface::pushEvent(mouseEvent);
	}
	
	void onMousePositionEvent(GLFWwindow* window, double xpos, double ypos) {
		InputEvent mouseEvent(INPUT_TYPE_MOUSE_POSITION);
		mouseEvent.setXPosition(xpos);
		mouseEvent.setYPosition(ypos);
		InputPluginInterface::pushEvent(mouseEvent);
	}
	
	GLFWInput::GLFWInput() : Dream::Plugins::Input::InputPluginInterface() {}
	GLFWInput::~GLFWInput() {}
	
	bool GLFWInput::init() {
		if (!mWindow) {
			std::cerr << "GLFWInput: Unable to initialise without a window reference."
			          << std::endl;
			return false;
		}
		std::cout << "GLFWInput: Initialising." << std::endl;
		glfwSetKeyCallback         (mWindow, onKeyboardEvent);
		glfwSetMouseButtonCallback (mWindow, onMouseButtonEvent);
		glfwSetScrollCallback      (mWindow, onMouseScrollEvent);
		glfwSetCursorPosCallback   (mWindow, onMousePositionEvent);
		std::cout << "GLFWInput: Init Complete." << std::endl;
		return true;
	}
	
	void GLFWInput::setWindow(GLFWwindow* window) {
		mWindow = window;
	}
	
	void GLFWInput::update(Dream::Scene::Scene *scene) {
		glfwPollEvents();
	}
	
} // End of GLFW
} // End of Input
} // End of Plugins
} // End of Dream