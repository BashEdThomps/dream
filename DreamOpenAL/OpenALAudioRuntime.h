/*
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

#pragma once

#include "ALHeader.h"
#include <DreamCore.h>
#include <deque>

using std::deque;
using glm::vec3;
using octronic::dream::AudioComponent;
using octronic::dream::AudioDefinition;
using octronic::dream::AudioComponent;
using octronic::dream::AudioLoader;
using octronic::dream::AudioStatus;
using octronic::dream::AudioMarkersUpdateTask;

namespace octronic::dream::open_al
{
    /**
     * @brief AudioRuntime data for an OpenAL based Audio Clip.
     */
    class OpenALAudioRuntime : public AudioRuntime
    {
    public:

        OpenALAudioRuntime(AudioLoader* loader, AudioDefinition* def, ProjectRuntime* project);
        ~OpenALAudioRuntime() override;

        bool useDefinition() override;
        void setSampleOffset(unsigned int offset) override;
        int getDurationInSamples() override;
        void setSourcePosision(vec3 pos) override;
        void setVolume(float volume) override;
        void play() override;
        void pause() override;
        void stop() override;
        AudioStatus getState() override;
        unsigned int getSampleOffset() const override;
        void setLooping(bool) override;

        ALsizei getFrequency()const ;
        ALenum  getFormat()const ;

        void setBuffer(ALuint buffer);
        ALuint getBuffer()const ;

        void setSource(ALuint source);
        ALuint getSource() const;

        AudioMarkersUpdateTask* getMarkersUpdateTask();

    protected:
        bool loadIntoAL();
        ALuint generateSource();
        ALuint generateBuffer();

    protected:
        ALenum mALFormat;
        ALuint mALSource;
        ALuint mALBuffer;
        ALint mALDurationInSamples;
    };
}
