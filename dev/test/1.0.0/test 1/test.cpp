#include <Ylona/Ylona.hpp>


int main(){

    Ylona::Ylona y;

    // récupère le volume actuel et l'affiche
    std::cout << y.getVolume()  << std::endl;

    if(y.isMuted() == true){
        y.setMute(false); // démute si le song et mute
        y.setVolume(30.0f); // monter le volume à 30 %
    }else{
        y.setVolume(50.0f); // monter le volume à 50 %
    }

    y.~Ylona(); // libère les ressources

    return 0;
}

//g++ -o test.exe test.cpp -lYlona -lole32 -lstdc++ -luuid