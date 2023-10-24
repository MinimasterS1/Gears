#include "gAudioMg.h"

#include <vorbis/codec.h>

#include <vorbis/vorbisfile.h>

#include <iostream>

SoundManager::SoundManager() {

    device = alcOpenDevice(NULL);
    if (!device) {
        std::cerr << "Failed to initialize OpenAL device." << std::endl;
        return;
    }

    context = alcCreateContext(device, NULL);
    if (!context) {
        std::cerr << "Failed to create OpenAL context." << std::endl;
        return;
    }

    alcMakeContextCurrent(context);
  
}

SoundManager::~SoundManager() {
    CleanUp();
    alcDestroyContext(context);
    alcCloseDevice(device);
}

bool LoadOggFile(const std::string& filePath, ALenum& format, ALsizei& size, ALvoid*& data, ALsizei& freq) {
    OggVorbis_File vorbisFile;
    if (ov_fopen(filePath.c_str(), &vorbisFile) < 0) {
        std::cerr << "Failed to open Ogg file: " << filePath << std::endl;
        return false;
    }

    vorbis_info* vorbisInfo = ov_info(&vorbisFile, -1);

    format = (vorbisInfo->channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
    freq = vorbisInfo->rate;
    size = static_cast<ALsizei>(ov_pcm_total(&vorbisFile, -1) * sizeof(short));
    data = malloc(size);

    size_t bytesRead = 0;
    while (true) {
        int section;
        long result = ov_read(&vorbisFile, static_cast<char*>(data) + bytesRead, size - bytesRead, 0, 2, 1, &section);

        if (result <= 0) {
            break;
        }

        bytesRead += result;
    }

    ov_clear(&vorbisFile);

    return true;
}

bool SoundManager::LoadSound(const std::string& filePath, const std::string& soundName) {
    ALuint buffer;
    alGenBuffers(1, &buffer);

    if (alGetError() != AL_NO_ERROR) {
        std::cerr << "Failed to generate OpenAL buffer." << std::endl;
        return false;
    }

    ALenum format;
    ALsizei size;
    ALvoid* data;
    ALsizei freq;
    ALboolean loop = AL_FALSE;

    if (!LoadOggFile(filePath, format, size, data, freq)) {
        std::cerr << "Failed to load Ogg file: " << filePath << std::endl;
        return false;
    }

    ALuint source;
    alGenSources(1, &source);
    alSourcef(source, AL_PITCH, 1);
    alSourcef(source, AL_GAIN, 1);
    alSource3f(source, AL_POSITION, 0, 0, 0);
    alSource3f(source, AL_VELOCITY, 0, 0, 0);
    alSourcei(source, AL_LOOPING, loop);
    alSourcei(source, AL_BUFFER, buffer);

    alBufferData(buffer, format, data, size, freq);

    buffers.push_back(buffer);
    sources.push_back(source);

    return true;
}

void SoundManager::PlaySound(const std::string& soundName) {
    for (size_t i = 0; i < sources.size(); i++) {
        if (soundName == "MySound") {
            alSourcePlay(sources[i]);
            return;
        }
    }
    std::cerr << "Sound not found: " << soundName << std::endl;
}

void SoundManager::CleanUp() {
    for (ALuint source : sources) {
        alDeleteSources(1, &source);
    }

    for (ALuint buffer : buffers) {
        alDeleteBuffers(1, &buffer);
    }

    sources.clear();
    buffers.clear();
}
