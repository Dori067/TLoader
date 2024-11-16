#include <iostream>
#include <filesystem>
#include <string>
#include <windows.h>
#include <shlobj.h>
#include <Lmcons.h>
#include <io.h>
#include <fcntl.h>
#include <fstream>

namespace fs = std::filesystem;

int movef(bool isjava, bool istl, bool isclient, bool ischanged) {

    std::locale::global(std::locale(""));
    //the folders must be in the same directory as the executable
    std::string javaf = "javat";
    std::string tlf = ".tlauncher";
    std::string clientf = ".minecraft";

    fs::path javaf_dir = fs::current_path() / javaf;
    fs::path tlf_dir = fs::current_path() / tlf;
    fs::path clientf_dir = fs::current_path() / clientf;

    std::string crp = fs::current_path().string();
        //std::string appdata_path = "%appdata%";
        //fs::path appdata_folder = appdata_path;

        //try {
        //    std::filesystem::copy(javaf_dir, appdata_folder);
        //}
        //catch (std::filesystem::filesystem_error& e) {
        //    std::cout << e.what() << '\n';
        //}
    char* user = getenv("username");
    std::string username(user, strlen(user));

    std::string replace =  username;
    std::string path = "C:\\Users\\x\\AppData\\Roaming";

    path.replace(9, 1, replace);

    fs::path appdata_dir = path;

    std::cout << path << std::endl;

    if (isjava == true && istl == true && isclient == true && ischanged == true) {
        std::cout << "all folders are found, and they are ready to be moved \n";
    }
    else {
        std::cout << "you missing something \n";
    }
    
    //copying the folders and files to the appdata folder using the "path" string....

    return 0;
};

int setdir(bool isjava, bool istl, bool isclient) {
    //_setmode(_fileno(stdout), _O_U16TEXT);
    bool ischanged;
    std::locale::global(std::locale(""));

    char* user = getenv("username");
    std::string username(user, strlen(user));
    std::cout << username << "\n";

    if (istl == true && isjava == true && isclient == true) {
        std::ofstream myfile;
            myfile.open(".tlauncher\\filename.txt", std::ios::app);

            if (myfile.is_open()) {
 
                if (isjava == true && istl == true && isclient == true) {
                    std::cout << "all folders are found \n";
                    myfile << "minecraft.gamedir=C\\:\\\\Users\\\\" << username << "\\\\AppData\\\\Roaming\\\\.minecraft\n";
                    myfile.close();
                    ischanged = true;
                    movef(isjava, istl, isclient, ischanged);
                }
                else {
                    std::cout << "you missing something \n";
                    ischanged = false;
                    return 0;
                }
            }
            else {
                std::cout << "Unable to open file. \n";
                return 0;
            }
        
    }
    //sets the game files directory for the launcher....

};

int main() {
    std::locale::global(std::locale(""));
    int num;
    bool ifjava;
    bool iftl;
    bool ifclient;
    // jdk xx.xx.x should be replaced by "java"
    //the folders must be in the same directory as the executable
    fs::path current_dir = fs::current_path();
    fs::path java_dir = current_dir / "java";
    fs::path client_dir = current_dir / ".minecraft";
    fs::path tl_dir = current_dir / ".tlauncher";

    std::cout << R"(
__/\\\\\\\\\\\\\\\__/\\\\\\_________________________________________/\\\_______________________________        
 _\///////\\\/////__\////\\\________________________________________\/\\\_______________________________       
  _______\/\\\__________\/\\\________________________________________\/\\\_______________________________      
   _______\/\\\__________\/\\\________/\\\\\_____/\\\\\\\\\___________\/\\\______/\\\\\\\\___/\\/\\\\\\\__     
    _______\/\\\__________\/\\\______/\\\///\\\__\////////\\\_____/\\\\\\\\\____/\\\/////\\\_\/\\\/////\\\_    
     _______\/\\\__________\/\\\_____/\\\__\//\\\___/\\\\\\\\\\___/\\\////\\\___/\\\\\\\\\\\__\/\\\___\///__   
      _______\/\\\__________\/\\\____\//\\\__/\\\___/\\\/////\\\__\/\\\__\/\\\__\//\\///////___\/\\\_________  
       _______\/\\\________/\\\\\\\\\__\///\\\\\/___\//\\\\\\\\/\\_\//\\\\\\\/\\__\//\\\\\\\\\\_\/\\\_________ 
        _______\///________\/////////_____\/////______\////////\//___\///////\//____\//////////__\///__________
)";
    std::cout << "By Dori067\n\n";
    if (fs::exists(java_dir) && fs::is_directory(java_dir)) {
        std::cout << "Java Found \n";
        ifjava = true;
    }
    else {
        std::cout << "Java Not Found \n";
        ifjava = false;
    };

    if (fs::exists(tl_dir) && fs::is_directory(tl_dir)) {
        std::cout << "Tl Found \n";
        iftl = true;
    }
    else {
        std::cout << "Tl Not Found \n";
        iftl = false;
    };

    if (fs::exists(client_dir) && fs::is_directory(client_dir)) {
        std::cout << "Client Found \n";
        ifclient = true;
    }
    else {
        std::cout << "Client Not Found \n";
        ifclient = false;
    };
    setdir(ifjava, iftl, ifclient);

    std::cout << ifjava << iftl << ifclient;
    std::cin >> num;
}