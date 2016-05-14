/*
* Dream::Resource::Model::Wavefront::ObjModel
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

#include "ObjModel.h"

#define TINYOBJLOADER_IMPLEMENTATION

namespace Dream {
	namespace Resource {
		namespace Instance {
			namespace Model {
				namespace WaveFront {

					ObjModelInstance::ObjModelInstance(void) :
						Dream::Resource::Instance::ResourceInstance() {

					}

					ObjModelInstance::~ObjModelInstance(void) {

					}

					void ObjModelInstance::generateAbsolutePaths(std::string projectDir,std::string projectUUID){
						mObjPath = projectDir         + PATH_SEP +
											 RESOURCE_DIR       + PATH_SEP +
											 RESOURCE_DIR_MODEL + PATH_SEP +
											 getUUID()          + PATH_SEP +
											 RESOURCE_FORMAT_OBJ;
						std::cout << "Generated path for obj resource: " << mObjPath << std::endl;
						/*
						mMtlPath = projectDir         + PATH_SEP +
											 RESOURCE_DIR       + PATH_SEP +
											 RESOURCE_DIR_MODEL + PATH_SEP +
											 getUUID()          + PATH_SEP +
											 RESOURCE_FORMAT_MTL;
						std::cout << "Generated path for mtl resource: " << mMtlPath << std::endl;
						*/
					}
				} // End of Wavefront
			} // End of Model
		} // End of Instance
	} // End of Resource
} // End of DreamFileFormats