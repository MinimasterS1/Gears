#pragma once

#include "al.h"
#include <alc.h>

#include <vector>
#include <string>

class SoundManager {
public:

    SoundManager(); 
    ~SoundManager(); 

  
    bool LoadSound(const std::string& filePath, const std::string& soundName);
    void PlaySound(const std::string& soundName);

   
    void CleanUp();

private:
    ALCdevice* device;
    ALCcontext* context;
    std::vector<ALuint> buffers;
    std::vector<ALuint> sources;

    struct SoundInfo {
        ALuint buffer;
        std::string name;
    };

    std::vector<SoundInfo> soundInfos;
  
};
