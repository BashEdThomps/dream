/*
* Dream::Components::Audio::OpenAL::AudioComponent
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

#include "AudioComponent.h"

#include <iostream>
namespace Dream {
  namespace Components {
    namespace Audio {

      AudioComponent::AudioComponent() : ComponentInterface() {}

      AudioComponent::~AudioComponent() {
      }

      bool AudioComponent::init() {
        std::cout << "AudioComponent: Initialising...";
        //Initialize SDL_mixer
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ) {
            std::cout << "AudioComponent: Error SDL_OpenAudio Failed" << std::endl;
            return false;
        }
        std::cout << "done." << std::endl;
        return true;
      }

      void AudioComponent::play(AudioInstance* asset) {
        // TODO
      }

      void AudioComponent::stop(AudioInstance* asset) {
        // TODO
      }

      void AudioComponent::pause(AudioInstance* asset) {
        // TODO
      }


      void AudioComponent::pushToPlayQueue(AssetInstance* asset) {
        try {
          if (std::find(mPlayQueue.begin(),mPlayQueue.end(), asset) == mPlayQueue.end()){
           AudioInstance* audioAsset;
            audioAsset = dynamic_cast<AudioInstance*>(asset);
            mPlayQueue.push_back(audioAsset);
          }
        } catch (const std::exception &ex) {
          std::cerr << "AudioComponent: Unable to push asset to play queue" << asset->getNameAndUUIDString() << std::endl
                    << ex.what() << std::endl;
        }
      }

      void AudioComponent::pushToPauseQueue(AssetInstance* asset) {
        try {
          if (std::find(mPauseQueue.begin(),mPauseQueue.end(), asset) == mPauseQueue.end()) {
            mPauseQueue.push_back(dynamic_cast<AudioInstance*>(asset));
          }
        }  catch (const std::exception &ex) {
          std::cerr << "AudioComponent: Unable to push asset to pause queue" << asset->getNameAndUUIDString() << std::endl
                    << ex.what() << std::endl;
        }
      }

      void AudioComponent::pushToStopQueue(AssetInstance* asset) {
        try {
          if (std::find(mStopQueue.begin(),mStopQueue.end(), asset) == mStopQueue.end()) {
            mStopQueue.push_back(dynamic_cast<AudioInstance*>(asset));
          }
        } catch (const std::exception &ex) {
          std::cerr << "AudioComponent: Unable to push asset to stop queue" << asset->getNameAndUUIDString() << std::endl
                    << ex.what() << std::endl;
        }
      }

      void AudioComponent::update(Scene*) {
        updatePlayQueue();
        updatePauseQueue();
        updateStopQueue();
      }

      void AudioComponent::updatePlayQueue() {
        std::vector<AudioInstance*>::iterator iterator;
        for (iterator = mPlayQueue.begin(); iterator != mPlayQueue.end(); iterator++) {
          AudioInstance *audioAsset = (*iterator);
          if (audioAsset->getStatus() != PLAYING){
            play(audioAsset);
          }
        }
        mPlayQueue.clear();
      }

      void AudioComponent::updatePauseQueue() {
        std::vector<AudioInstance*>::iterator iterator;
        for (iterator = mPauseQueue.begin(); iterator != mPauseQueue.end(); iterator++) {
          AudioInstance *audioAsset = (*iterator);
          if (audioAsset->getStatus() != PAUSED) {
            pause(audioAsset);
          }
        }
        mPauseQueue.clear();
      }

      void AudioComponent::updateStopQueue() {
        std::vector<AudioInstance*>::iterator iterator;
        for (iterator = mStopQueue.begin(); iterator != mStopQueue.end(); iterator++) {
          AudioInstance *audioAsset = (*iterator);
          if (audioAsset->getStatus() != STOPPED) {
            stop(audioAsset);
          }
        }
        mStopQueue.clear();
      }

      void AudioComponent::playAsset(AssetInstance *asset) {
        pushToPlayQueue(asset);
      }

      void AudioComponent::pauseAsset(AssetInstance *asset) {
        pushToPauseQueue(asset);
      }

      void AudioComponent::stopAsset(AssetInstance *asset) {
        pushToStopQueue(asset);
      }

    } // End of Audio
  } // End of Components
} // End of Dream
