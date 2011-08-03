#include "Util.hpp"

namespace util {

bool InitGlew() {
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Error initializing GLEW." << std::endl;
    } else {
        std::cout << "Using GLEW Version: " << glewGetString(GLEW_VERSION) << std::endl;
    }
    return err == GLEW_OK;
}

std::string LoadFile(const char *path) {
    std::ifstream file;
    file.open(path, std::ios::in);
    if(!file.is_open()) {
        std::cerr << "Could not open file: " << path << std::endl;
        return "";
    }
    std::string line, data;
    while(file.good()) {
        std::getline(file,line);
        data += line + "\n";
    }
    file.close();
    return data;
}

} // namespace util
