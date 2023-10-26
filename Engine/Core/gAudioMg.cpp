#include "gAudioMg.h"

#include "gSoundDevice.h"
#include "gSoundEffectsPlayer.h"
#include "gSoundEffectsLib.h"

#include <iostream>


SoundDevice* sd = LISTENER->Get();
int SciFiSound = SE_LOAD("Content/Audio/02.ogg");
SoundEffectsPlayer sound_effects_player_forSciFiSound;


void SoundManager::Init()

{
	ALint attunation = AL_INVERSE_DISTANCE_CLAMPED;
	sd->SetAttunation(attunation);
	sd->SetLocation(0.f, 0.f, 0.f);
	sd->SetOrientation(0.f, 1.f, 0.f, 0.f, 0.f, 1.f);

	sound_effects_player_forSciFiSound.SetLooping(true);
	sound_effects_player_forSciFiSound.SetPosition(0.0f, 0.0f, 0.0f);
	//sound_effects_player_forSciFiSound.Play(SciFiSound);
}


void SoundManager::PlayMusic() 
{
	sound_effects_player_forSciFiSound.Play(SciFiSound);

}

void SoundManager::StopMusic()
{
	sound_effects_player_forSciFiSound.Stop();

}