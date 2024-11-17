#include <iostream>
#include <filesystem>
#include <string>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include <fstream>
#include <chrono>
#include <thread>
#include <cstdio>

namespace fs = std::filesystem;

int movef(bool isjava, bool istl, bool isclient, bool ischanged, bool defjava) {

    std::locale::global(std::locale(""));
    //the folders must be in the same directory as the executable
    std::string javaf = "javap";
    std::string tlf = ".tlauncher";
    std::string clientf = ".minecraft";

    fs::path javaf_dir = fs::current_path() / javaf;
    fs::path tlf_dir = fs::current_path() / tlf;
    fs::path clientf_dir = fs::current_path() / clientf;

    std::string crp = fs::current_path().string();
    char* user = getenv("username");
    std::string username(user, strlen(user));

    std::string replace =  username;
    std::string path = "C:\\Users\\x\\AppData\\Roaming";

    path.replace(9, 1, replace);

    fs::path appdata_dir = path;

    std::cout << path << std::endl;

    if (isjava == true && istl == true && isclient == true && ischanged == true) {
        std::cout << "All required folders are found, and they are ready to be moved. \n";
        //this moves the "javap" folder too, but there will be that only moves the .tl and .mine folders
        //copying the folders and files to the appdata folder using the "path" string...
    }
    else {
        std::cout << "You are missing something \n";
    }
    
    return 0;
};

int setdir(bool isjava, bool istl, bool isclient, bool defjava) {
    bool ischanged;
    std::locale::global(std::locale(""));

    char* user = getenv("username");
    std::string username(user, strlen(user));
    std::cout << username << "\n";

    if (istl == true && isclient == true && isjava == true or defjava == true) {
        std::ifstream file(".tlauncher\\tlauncher-2.0.properties");
        if (!file.is_open()) {
            std::cerr << "Cant open file." << std::endl;

        }
        std::vector<std::string> lines;
        std::string line;
        while (getline(file, line)) {
            if (line.find("minecraft.gamedir=") == 0) {
                std::cout << "Found line: " << line << std::endl;
                
                std::ifstream source_file(".tlauncher\\tlauncher-2.0.properties");
                std::ofstream destination_file(".tlauncher\\temp1.txt");

                if (!source_file.is_open()) {
                    std::cerr << "Cant open main file." << std::endl;
                    return 1;
                }

                if (!destination_file.is_open()) {
                    std::cerr << "Cant open temp file." << std::endl;
                    source_file.close();

                }
                char ch;
                while (source_file.get(ch)) {
                    destination_file << ch;
                }

                source_file.close();
                destination_file.close();
                std::this_thread::sleep_for(std::chrono::seconds(2));
                std::ifstream input_file(".tlauncher\\temp1.txt");
                std::ofstream output_file(".tlauncher\\tlauncher-2.0.properties");
                std::string line;
                while (getline(input_file, line)) {
                    if (line.find("minecraft.gamedir=") == 0) {
                        output_file << "minecraft.gamedir=C\\:\\\\Users\\\\" << username << "\\\\AppData\\\\Roaming\\\\.minecraft\n";
                        ischanged = true;
                        //movef();
                    }
                    else {
                        output_file << line << "\n";
                    }
                }

                input_file.close();
                output_file.close();

                //std::this_thread::sleep_for(std::chrono::seconds(5));
            }
        }
    }
    else {
        std::cout << "Please check your files and folders.";
    }

};

int checkex() {
    std::locale::global(std::locale(""));
    bool defjava = false;
    bool ifjava;
    bool iftl;
    bool ifclient;
    //jdk xx.xx.xx should be replaced by "javap" if you are using a portable version of java
    //the folders must be in the same directory as the executable
    fs::path current_dir = fs::current_path();
    fs::path java_dir = current_dir / "javap";
    fs::path client_dir = current_dir / ".minecraft";
    fs::path tl_dir = current_dir / ".tlauncher";

    if (fs::exists(java_dir) && fs::is_directory(java_dir)) {
        std::cout << "Java Found \n";
        ifjava = true;
    }
    else {
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


    if (ifjava == true) {
        std::string command = "java -version";
        int result = system(command.c_str());
        if (result == 0) {
            std::cout << "Java is installed by default on this machine." << std::endl;
            ifjava = true;
            defjava = true;
            setdir(ifjava, iftl, ifclient, defjava);
        }
        else {
            ifjava = true;
            defjava = false;
            setdir(ifjava, iftl, ifclient, defjava);
        }
    }
    else {
        std::string command = "java -version";
        int result = system(command.c_str());
        if (result == 0) {
            std::cout << "Java is installed by default on this machine." << std::endl;
            ifjava = false;
            defjava = true;
            setdir(ifjava, iftl, ifclient, defjava);
        }
        else {
            std::cout << "Java is not installed and not found in the folders." << std::endl;
            ifjava = false;
            defjava = false;
            setdir(ifjava, iftl, ifclient, defjava);
        }
    }
};

int launch(bool ftls, bool fcls, bool fjvs, bool fjav) {
    std::locale::global(std::locale(""));
    if (ftls == true && fcls == true && fjav == true) {
        std::locale::global(std::locale(""));
        char* user = getenv("username");
        std::string username(user, strlen(user));
        std::string tls = "C:\\Users\\" + username + "\\AppData\\Roaming\\.minecraft\\TLauncher.exe";
        std::string cmd = "java -jar C:\\Users\\" + username + "\\AppData\\Roaming\\.minecraft\\TLauncher.exe";
        fs::path tl_dir = tls;
        if (fs::exists(tls)) {
            int result = system(cmd.c_str());
            std::this_thread::sleep_for(std::chrono::seconds(3));
            return 0;
        }
    }
    if (ftls == true && fcls == true && fjav == false && fjvs == true) {
        std::locale::global(std::locale(""));
        char* user = getenv("username");
        std::string username(user, strlen(user));
        std::string tls = "C:\\Users\\" + username + "\\AppData\\Roaming\\.minecraft\\TLauncher.exe";
        std::string cmd = "C:\\Users\\" + username + "\\AppData\\Roaming\\javap\\bin\\java.exe" + "-jar" + "C:\\Users\\" + username + "\\AppData\\Roaming\\.minecraft\\TLauncher.exe";
        fs::path tl_dir = tls;
        if (fs::exists(tls)) {
            int result = system(cmd.c_str());
            std::this_thread::sleep_for(std::chrono::seconds(3));
            return 0;
        }
    }
}

int isinstalled() {
    std::locale::global(std::locale(""));

    bool ftls = false;
    bool fcls = false;
    bool fjvs = false;
    bool fjav = false;

    char* user = getenv("username");
    std::string username(user, strlen(user));
    std::string cls = "C:\\Users\\" + username + "\\AppData\\Roaming\\.minecraft";
    std::string tls = "C:\\Users\\" + username + "\\AppData\\Roaming\\.tlauncher";
    std::string jvs = "C:\\Users\\" + username + "\\AppData\\Roaming\\javap";
    fs::path tl_dir = tls;
    fs::path client_dir = cls;
    fs::path javaport_dir = jvs;

    if (fs::exists(tls)) {
        ftls = true;
    }
    if (fs::exists(cls)) {
        fcls = true;
    }
    if (fs::exists(jvs)) {
        fjvs = true;
    }

    std::string command = "java -version";
    int result = system(command.c_str());
    if (result == 0) {
        fjav = true;

    }
    else {
        fjav = false;
    }
    std::cout << ftls << fcls << fjvs << fjav;
    if (ftls == false && fcls == false) {
        checkex();
    }
    if (ftls == true && fcls == true) {
        launch(ftls, fcls, fjvs, fjav);
    }

}

int main() {
    std::locale::global(std::locale(""));
    int num;

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
    //launch();
    //checkex();
    isinstalled();
}