#ifndef DREAM_H
#define DREAM_H

#include <iostream>

#include "ArgumentParser.h"

#include "../JSON/json.hpp"
#include "../Util/FileReader.h"
#include "../Scene/Scene.h"
#include "../Project/Project.h"
#include "../Asset/AssetInstance.h"


namespace Dream {
	
	class Dream {
	protected:
		Project::Project *mProject;
		bool              mRunning;

	public:
		Dream(void);
		~Dream(void);

		bool loadFromArgumentParser(ArgumentParser*);
		bool loadProjectFromFileReader(std::string projectPath, Util::FileReader*);
		bool loadScene(Scene::Scene*);

		Project::Project* getProject(void);
		void setProject(Project::Project*);
		bool runProject();
		bool isProjectLoaded();
	};
	
} // End of Dream

#endif // DREAM_H
