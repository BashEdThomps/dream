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

#include "OggLoader.h"

#include <Common/Logger.h>
#include "Storage/StorageManager.h"
#include "Storage/File.h"
#include "Storage/ProjectDirectory.h"
#include "Project/Project.h"
#include "Project/ProjectRuntime.h"
#include "Components/Audio/AudioDefinition.h"

#include <vorbis/vorbisfile.h>

using octronic::dream::File;


static size_t seekIndex = 0;

size_t octronic_dream_oggloader_read
(void* buffer, size_t elementSize, size_t elementCount, void* dataSource)
{
    // copy the next elementCount bytes from dataSource into buffer
	assert(elementSize == 1);
    File* f = (File*)dataSource;
    size_t capped_count = 0;
    if(seekIndex+elementCount > f->getBinaryDataSize())
    {
       size_t overflow =  (seekIndex+elementCount) - f->getBinaryDataSize();
       capped_count = elementCount-overflow;
    }
    else
    {
        capped_count = elementCount;
    }
    //LOG_TRACE("OggLoader: Accessing index[{}/{}] Requesting {} elements (capped to {})",
    //          seekIndex, f->getBinaryDataSize(), elementCount,capped_count);
    uint8_t* data = f->getBinaryData();
    memcpy(buffer,&data[seekIndex], capped_count);
    seekIndex += capped_count;
    return capped_count;
}

namespace octronic::dream
{
	const uint16_t OggLoader::OGG_LOAD_BUFFER_SIZE = 1024;

    OggLoader::OggLoader()
        : AudioLoader()
    {
        LOG_TRACE("OggLoader: {}",__FUNCTION__);
    }

    OggLoader::~OggLoader()
    {
        LOG_TRACE("OggLoader: {}",__FUNCTION__);
    }

    bool
    OggLoader::loadIntoBuffer
    (AudioDefinition* audioDefinition, ProjectRuntime* projectRuntime)
    {
        LOG_TRACE("OggLoader: {}",__FUNCTION__);

        Project* project = projectRuntime->getProject();
        ProjectDirectory* pd = project->getDirectory();
        auto absPath = pd->getAssetAbsolutePath(audioDefinition);
        LOG_DEBUG("OggLoader: Loading Runtime: {}", absPath);


        // Open/Read the file
        StorageManager* sm = projectRuntime->getStorageManager();
        File *file = sm->openFile(absPath);
        if (file == nullptr || !file->exists())
        {
            LOG_ERROR("OggLoader: Cannot open {} for reading, may not exist", absPath);
            return false;
        }

        if (!file->readBinary())
        {
            LOG_ERROR("OggLoader: Error reading binary data");
            sm->closeFile(file);
            file = nullptr;
            return false;
        }

        // Setup Callbacks
        ov_callbacks callbacks;
        memset(&callbacks,0,sizeof(ov_callbacks));
        callbacks.read_func  = octronic_dream_oggloader_read;
        callbacks.seek_func  = NULL;//octronic_dream_oggloader_seek;
        callbacks.tell_func  = NULL;//octronic_dream_oggloader_tell;
        callbacks.close_func = NULL;
        seekIndex = 0;

        // Try opening the given file
        OggVorbis_File oggFile;
        int error = ov_open_callbacks(file, &oggFile, nullptr, 0, callbacks);
        if (error < 0)
        {
            LOG_ERROR("OggLoader: Error opening {} for decoding, ov_open failed\n\t{}", absPath, getOggErrorString(error));
            return false;
        }

        // Get some information about the OGG file
        vorbis_info *oggInfo;
        oggInfo = ov_info(&oggFile, -1);

        // Check the number of channels... always use 16-bit samples
        if (oggInfo->channels == 1)
        {
            mChannels = 1;
        }
        else
        {
            mChannels = 2;
        }

        // The frequency of the sampling rate
        mSampleRate = oggInfo->rate;

        // Keep reading until all is read
        int bitStream = 0;
        long bytes = 0;
        char fixed_buffer[OGG_LOAD_BUFFER_SIZE];
        vector<uint8_t> expanding_buffer;
        do
        {
            // Read up to a buffer's worth of decoded sound data
            // 0 for Little-Endian, 1 for Big-Endian
            bytes = ov_read(&oggFile, &fixed_buffer[0], OGG_LOAD_BUFFER_SIZE, 0, 2, 1, &bitStream);

            if (bytes < 0)
            {
                ov_clear(&oggFile);
                LOG_ERROR("OggLoader: Error decoding {}", absPath);
                return false;
            }
            // Append to end of buffer
            expanding_buffer.insert(expanding_buffer.end(), &fixed_buffer[0], &fixed_buffer[0] + bytes);
        }
        while (bytes > 0);
        mAudioBuffer = new uint8_t[expanding_buffer.size()];
        mAudioBufferSize = expanding_buffer.size();
        memcpy(mAudioBuffer, &expanding_buffer[0], expanding_buffer.size());

        // Clean up!
        ov_clear(&oggFile);
        sm->closeFile(file);

        return checkLoaded();

    }

    string OggLoader::getOggErrorString(int error)
    {
       switch(error)
       {
           case OV_EREAD:
               return "OV_EREAD: A read from media returned an error.";
           case OV_ENOTVORBIS:
               return "OV_ENOTVORBIS: Bitstream does not contain any Vorbis data.";
           case OV_EVERSION:
               return "OV_EVERSION: Vorbis version mismatch.";
           case OV_EBADHEADER:
               return "OV_EBADHEADER: Invalid Vorbis bitstream header.";
           case OV_EFAULT:
               return "OV_EFAULT: Internal logic fault; indicates a bug or heap/stack corruption.";
           default:
               return "Unknown Error";
       }
    }
} // End of Dream
