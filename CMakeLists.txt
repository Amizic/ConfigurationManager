cmake_minimum_required(VERSION 3.14)
project(ConfigurationManager VERSION 1.0 LANGUAGES CXX)

# Option to build shared library (default static)
option(BUILD_SHARED_LIBS "Build as shared library (DLL)" OFF)

# Library target
add_library(ConfigurationManager
    src/ConfigurationManager.cpp
)

# Public include directory for anyone linking against 'ConfigurationManager'
target_include_directories(ConfigurationManager PUBLIC include)

# When building shared, define the DLL export macros
if(BUILD_SHARED_LIBS)
    target_compile_definitions(ConfigurationManager PRIVATE CONFIGURATIONMANAGER_DYNAMIC CONFIGURATIONMANAGER_BUILD)
    target_compile_definitions(ConfigurationManager INTERFACE CONFIGURATIONMANAGER_DYNAMIC)
endif()

# Optional: set C++ standard
target_compile_features(ConfigurationManager PUBLIC cxx_std_17)
