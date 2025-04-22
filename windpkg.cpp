#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <cstdlib>
#include <filesystem>

using json = nlohmann::json;
namespace fs = std::filesystem;

void installPackages() {
    std::ifstream confFile("windpkg.json");
    std::ifstream registryFile("windpkg/windpkg-registry.json");
    if (!confFile || !registryFile) {
        std::cerr << "Missing windpkg.json or registry.\n";
        return;
    }

    json conf = json::parse(confFile);
    json registry = json::parse(registryFile);
    auto deps = conf["dependencies"];

    fs::create_directory("wind_modules");

    for (auto& [pkg, version] : deps.items()) {
        std::string url = registry[pkg][version];
        std::string zipFile = "wind_modules/" + pkg + ".zip";
        std::string extractDir = "wind_modules/" + pkg;

        std::cout << "Installing " << pkg << "@" << version << "...\n";
        std::string cmd = "curl -L " + url + " -o " + zipFile;
        system(cmd.c_str());

        std::string unzipCmd = "unzip -o " + zipFile + " -d " + extractDir;
        system(unzipCmd.c_str());
    }

    std::cout << "All packages installed.\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: windpkg install\n";
        return 1;
    }

    std::string cmd = argv[1];
    if (cmd == "install") {
        installPackages();
    } else {
        std::cerr << "Unknown command.\n";
    }

    return 0;
}
