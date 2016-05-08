#include "embindcefv8.h"

#include <Urho3D/Audio/Sound.h>
#include <Urho3D/Audio/SoundSource.h>

using namespace Urho3D;

EMBINDCEFV8_DECLARE_CLASS(Context);

EMBINDCEFV8_BINDINGS(audio)
{
    embindcefv8::Class<SoundSource>("Sound")
        ;

    embindcefv8::Class<SoundSource>("SoundSource")
        .constructor<Context*>()
        .method("play", static_cast<void (SoundSource::*)(Sound*, float, float, float)>(&SoundSource::Play))
        .method("stop", &SoundSource::Stop)
        .method("setSoundType", &SoundSource::SetSoundType)
        .method("setFrequency", &SoundSource::SetFrequency)
        .method("setGain", &SoundSource::SetGain)
        .method("setAttenuation", &SoundSource::SetAttenuation)
        .method("setPanning", &SoundSource::SetPanning)
        ;
}