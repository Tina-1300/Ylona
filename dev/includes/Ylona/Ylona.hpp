#pragma once 
#include <windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <stdexcept>
#include <iostream>


/*
permet de géré le volume du song sous windows
-------------------
compilation :
g++ -o test.exe test.cpp -lYlona -lole32 -lstdc++ -luuid
*/

// Version 1.0.0
namespace Ylona{

    class Ylona{
        public:
            Ylona();
            ~Ylona();

            float getVolume();
            bool setVolume(float volume);
            bool isMuted();
            bool setMute(bool mute);


        private:
            IAudioEndpointVolume* endpointVolume;
            void initialize();
    };
    

};

