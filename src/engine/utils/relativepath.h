#pragma once
#include <windows.h>
#include <filesystem>

namespace Engine {

    std::filesystem::path getExecutableDir()
    {
        char buffer[MAX_PATH];
        GetModuleFileNameA(NULL, buffer, MAX_PATH);
        return std::filesystem::path(buffer).parent_path();
    }
}