# Configuration Manager
Configuration manager library made in C++, for reading configuration file key-value pairs, and storing them in memory.

## Usage
All classes live in the `ConfigurationManager` namespace, and the header is
`ConfigurationManager.hpp`:

```cpp
#include "ConfigurationManager.hpp"

ConfigurationManager::ConfigurationManager config;
if (config.loadFromFile("config.cfg") != 0) {
    // 0 = success, -1 = file could not be opened
}

std::string host = config.getValue("host", "127.0.0.1");
int port = std::stoi(config.getValue("port", "5555"));
config.setValue("debug_mode", "true");   // programmatic override
```

Values are stored and returned as strings — cast them when reading
(e.g. `std::stoi`). Config files use `key: value` lines; `#` starts a comment;
empty lines are skipped.

## Building the Library
### Static Build
`cmake -B build_static -G "MinGW Makefiles"`
`cmake --build build_static`

### Dynamic Build
`cmake -B build_shared -G "MinGW Makefiles" -DBUILD_SHARED_LIBS=ON`
`cmake --build build_shared`

## Building Tests
### Static Library Test
`g++ -std=c++17 tests/test_config.cpp -Iinclude -Lbuild_static -lConfigurationManager -o tests/test_config.exe`

### Dynamic Library Test
`g++ -std=c++17 tests/test_config.cpp -Iinclude -DCONFIGURATIONMANAGER_DYNAMIC -Lbuild_shared -lConfigurationManager -o tests/test_config_dynamic.exe`
