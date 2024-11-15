#include <iostream>
#include <filesystem>
#include <string>
#include <windows.h>
#include <shlobj.h>
#include <Lmcons.h>
#include <io.h>
#include <fcntl.h>

namespace fs = std::filesystem;

int movef(bool isjava, bool istl, bool isclient) {

    std::locale::global(std::locale(""));

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

    std::cout << path << std::endl;

    //std::cout << crp << "\n";


    //copying the folders and files to the appdata folder using the "path" string....


    return 0;
};

int setdir() {
    //_setmode(_fileno(stdout), _O_U16TEXT);
    std::locale::global(std::locale(""));

    char* user = getenv("username");
    std::string username(user, strlen(user));
    std::cout << username << "\n";


    //sets the game files directory for the launcher....


    return 0;
};

int main() {
    std::locale::global(std::locale(""));
    int num;
    bool ifjava;
    bool iftl;
    bool ifclient;
    // jdk xx.xx.x should be replaced by "java"
    fs::path current_dir = fs::current_path();
    fs::path java_dir = current_dir / "java";
    fs::path client_dir = current_dir / ".minecraft";
    fs::path tl_dir = current_dir / ".tlauncher";


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
    setdir();
    movef(ifjava, iftl, ifclient);

    std::cout << ifjava << iftl << ifclient;
    std::cin >> num;
}