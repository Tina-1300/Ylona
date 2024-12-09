#include "../../includes/Ylona/Ylona.hpp"

namespace Ylona{

    
    Ylona::Ylona() : endpointVolume(nullptr){
        initialize();
    };
    
    
    Ylona::~Ylona(){
        if (endpointVolume){
            endpointVolume->Release();
        }
        CoUninitialize();
    };

    // retourne le volume actuelle
    float Ylona::getVolume(){
        float currentVolume = 0.0f;
        HRESULT hr = endpointVolume->GetMasterVolumeLevelScalar(&currentVolume);
        if (FAILED(hr)){
            throw std::runtime_error("Failed to get current volume level.");
        }
        return currentVolume * 100; 
    };

    // permet de régler le volume return false si il y a un problème et true si tout ses bien 
    //passer
    bool Ylona::setVolume(float volume){
        if (volume < 0.0f || volume > 100.0f){
            throw std::invalid_argument("Volume must be between 0 and 100.");
            return false;
        }
        HRESULT hr = endpointVolume->SetMasterVolumeLevelScalar(volume / 100.0f, nullptr);
        if (FAILED(hr)){
            throw std::runtime_error("Failed to set volume level.");
            return false;
        }
        return true;
    };

    // return true si le son et mut et false si le son n'est pas mut
    bool Ylona::isMuted(){
        BOOL isMuted = FALSE;
        HRESULT hr = endpointVolume->GetMute(&isMuted);
        if (FAILED(hr)){
            throw std::runtime_error("Failed to get mute status.");
        }
        return isMuted;
    };

    // fonction qui permet de mute ou ne pas mute de son
    // si il et à true alor on mut 
    // si il et à false alor on démute
    // return true si tout ses bien passé et false si il y a eu des error
    bool Ylona::setMute(bool mute){
        HRESULT hr = endpointVolume->SetMute(mute, nullptr);
        if (FAILED(hr)){
            throw std::runtime_error("Failed to set mute status.");
            return false;
        }
        return true;
    };


    
            
    void Ylona::initialize(){
        CoInitialize(nullptr);

        IMMDeviceEnumerator* deviceEnumerator = nullptr;
        HRESULT hr = CoCreateInstance(
            __uuidof(MMDeviceEnumerator),
            nullptr,
            CLSCTX_ALL,
            __uuidof(IMMDeviceEnumerator),
            (void**)&deviceEnumerator);

        if (FAILED(hr) || !deviceEnumerator){
            throw std::runtime_error("Failed to create device enumerator.");
        }

        IMMDevice* defaultDevice = nullptr;
        hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
        deviceEnumerator->Release();

        if (FAILED(hr) || !defaultDevice){
            throw std::runtime_error("Failed to get default audio endpoint.");
        }

        hr = defaultDevice->Activate(
            __uuidof(IAudioEndpointVolume),
            CLSCTX_ALL,
            nullptr,
            (void**)&endpointVolume);
        defaultDevice->Release();

        if (FAILED(hr) || !endpointVolume){
            throw std::runtime_error("Failed to activate audio endpoint.");
        }
    };


};
    

