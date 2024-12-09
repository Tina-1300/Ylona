### Library Ylona Version (1.0.0)    
<img src="./Ylona.png" alt="Ylona" style="width: 90px; height: auto;">
---

<br>

## Organization :

After installing the *Ylona* library, to access the methods, 
you must use the namespace **Ylona**.
In this namespace, there is a class named **Ylona**.
This class contains all the library methods.


## Compilation information : 

To compile a program that uses the Ylona library, you must compile it with the following command :

````bash
g++ -o test.exe test.cpp -lYlona -lole32 -lstdc++ -luuid
````
This command links the Ylona library along with the necessary dependencies (ole32, stdc++, and uuid), allowing the program to function correctly.

---

<br>


### Method : `getVolume()`

**Description** :  
Allows you to retrieve the current volume value. 

#### Settings :
- `None` :  No settings.
  
#### Returned value :
- `float` : Returns the current volume.

#### Example of use :

````cpp
#include "Ylona/Ylona.hpp"

int main(){
    Ylona::Ylona y;

    float resultat = y.getVolume();
    std::cout << resultat << std::endl;

    return 0;
}
````

<br>
---
<br>

### Method : `setVolume()`

**Description** :  
Allows you to set the volume level of the audio device. This function takes a float number between 0 and 100, representing volume as a percentage.

#### Settings :
- `float volume` :  The volume to define must be a number between 0.0 and 100.0 (inclusive).
  
#### Returned value :
- `bool` : Returns `true` if the volume was correctly modified, `false` in case of error.

#### Example of use :

````cpp
#include "Ylona/Ylona.hpp"

int main(){
    Ylona::Ylona y;

    if(y.setVolume(50.0f) == true){
        std::cout << "Sucess" << std::endl;
    }else{
        std::cout << "Error" << std::endl;
    }

    return 0;
}
````

<br>
---
<br>

### Method : `isMuted()`

**Description** :  
Returns whether the audio device is currently muted or not. This function checks if the sound is muted and returns a boolean value.

#### Settings :
- `None` :  No parameters..
  
#### Returned value :
- `bool` : Returns `true` if the audio is muted, `false` if it is not muted.

#### Example of use :

````cpp
#include "Ylona/Ylona.hpp"

int main(){
    Ylona::Ylona y;

    bool isMuted = y.isMuted();
    if (isMuted){
        std::cout << "The audio is muted." << std::endl;
    }else{
        std::cout << "The audio is not muted." << std::endl;
    }

    return 0;
}
````

<br>
---
<br>

### Method : `setMute()`

**Description** :  
Sets the mute status of the audio device. This function allows you to mute or unmute the audio depending on the value passed to it.

#### Settings :
- `bool mute` :  A boolean value. Pass true to mute the audio, or false to unmute it.
  
#### Returned value :
- `bool` : Returns `true` if the mute status was successfully set, `false` in case of an error.

#### Example of use :

````cpp
#include "Ylona/Ylona.hpp"

int main(){
    Ylona::Ylona y;

    // Mute the audio
    if (y.setMute(true)){
        std::cout << "The audio has been muted." << std::endl;
    }else{
        std::cout << "Failed to mute the audio." << std::endl;
    }

    // Unmute the audio
    if (y.setMute(false)){
        std::cout << "The audio has been unmuted." << std::endl;
    }else{
        std::cout << "Failed to unmute the audio." << std::endl;
    }

    return 0;
}
````