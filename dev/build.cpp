#include <iostream>
#include <filesystem>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>

//https://semver.org/lang/fr/

//https://cocomelonc.github.io/page26/

// g++ -o build.exe build.cpp & color

const std::string VERSION = "1.0.0"; // Version de la library
const std::string NAME = "Ylona";

const std::string src_dir = "src/"+NAME;
const std::string include_dir = "includes/"+NAME;
const std::string obj_dir = "obj";



const std::string build_dir_Windows = "../build/Release/Windows/"+VERSION;
const std::string build_dir_Linux = "../build/Release/Linux/"+VERSION;
const std::string build_dir_Macos = "../build/Release/Macos/"+VERSION;


const std::string include_build_dir_Windows = build_dir_Windows + "/includes/Ylona/";
const std::string lib_build_dir_Windows = build_dir_Windows + "/lib";


void clean_directory(const std::string& directory){
    try{
        for (const auto& entry : std::filesystem::directory_iterator(directory)){
            const auto& file_path = entry.path();
            if (std::filesystem::is_directory(file_path)){
                std::filesystem::remove_all(file_path); 
            }else{
                std::filesystem::remove(file_path);
            }
        }
    }catch (const std::exception& e){
        std::cerr << "Erreur lors de la suppression de " << directory << " : " << e.what() << std::endl;
    }
}

// Fonction pour compiler les fichiers .cpp en fichiers .o
void compile_cpp_to_obj(){
    for (const auto& entry : std::filesystem::directory_iterator(src_dir)) {
        const auto& file_path = entry.path();
        if (file_path.extension() == ".cpp"){
            std::string cpp_file = file_path.string();
            std::string obj_file = obj_dir + "/" + file_path.stem().string() + ".o";

            std::string command = "g++ -c " + cpp_file + " -I" + include_dir + " -o " + obj_file;
            int result = std::system(command.c_str());
            if (result != 0){
                std::cerr << "Erreur lors de la compilation de " << cpp_file  << std::endl;
                return;
            }
        }
    }
};

// Fonction pour compiler la library static en .a
void create_static_lib(){
    #ifdef _WIN64
        std::string lib_file = lib_build_dir_Windows + "/libYlona.a";
        std::string command = "ar rvs " + lib_file;
        for (const auto& entry : std::filesystem::directory_iterator(obj_dir)){
            const auto& file_path = entry.path();
            if (file_path.extension() == ".o"){
                command += " " + file_path.string();
            }
        }
        command += " > nul 2>&1";
        int result = std::system(command.c_str());
        if (result != 0){
            std::cerr << "Erreur lors de la compilation de la library statique" << std::endl;
        }
    #endif
};


void move_files(){
    for (const auto& entry : std::filesystem::directory_iterator(include_dir)){
        const auto& file_path = entry.path();
        if (file_path.extension() == ".hpp"){
            std::filesystem::copy(file_path, include_build_dir_Windows + "/" + file_path.filename().string());
        }
    }

    std::string lib_file = lib_build_dir_Windows + "/libYlona.a";
    if (std::filesystem::exists(lib_file)){
        std::cout << "Success Compilation Static" << std::endl;
    }else{
        std::cerr << "Erreur lors de la compilation des fichiers statiques" << std::endl;
    }
};

int main(){
    SetConsoleOutputCP(CP_UTF8);


    try{
        system("color 4");
        if (!std::filesystem::exists(obj_dir)){
            std::filesystem::create_directories(obj_dir);
        }
        if(!std::filesystem::exists(include_build_dir_Windows)){
            std::filesystem::create_directories(include_build_dir_Windows);
        }
        if (!std::filesystem::exists(lib_build_dir_Windows)){
            std::filesystem::create_directories(lib_build_dir_Windows);
        }


        clean_directory(obj_dir);            
        clean_directory(include_build_dir_Windows);  
        clean_directory(lib_build_dir_Windows);  

        compile_cpp_to_obj();  
        create_static_lib();  
        move_files();
        std::cout << "Success Compilation" << std::endl;
    }catch (const std::exception& e){
        std::cerr << "Une erreur s'est produite : " << e.what() << std::endl;
    }

    std::cout << "Appuyez sur Entrer pour fermer..." << std::endl;
    std::cin.get();

    return 0;
}

