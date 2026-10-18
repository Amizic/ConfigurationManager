# ConfigurationManager

Configuration manager library made in C++, for reading configuration file
key-value pairs and storing them in memory. One class, one header:

```cpp
#include "ConfigurationManager.hpp"   // namespace ConfigurationManager
```

Config files use `key: value` lines; `#` starts a comment; empty lines are
skipped. Values are stored and returned as strings — cast them when reading
(e.g. `std::stoi` for numbers).

## API reference

### ConfigurationManager

#### `ConfigurationManager::ConfigurationManager()`
Creates an empty configuration. Nothing is loaded until `loadFromFile()`.
- **Returns:** nothing (constructor).

#### `ConfigurationManager::loadFromFile(filePath)`
Loads and parses a config file into memory. Replaces previously loaded
values for keys that exist in the file; other keys are kept.
- **In:** `filePath` — `std::string`, path to the config file.
- **Returns:** `0` on success, `-1` if the file cannot be opened.

#### `ConfigurationManager::keyExists(key)`
- **In:** `key` — `std::string`.
- **Returns:** `true` if the key is present, `false` otherwise.

#### `ConfigurationManager::getValue(key)`
Looks up a value without a fallback.
- **In:** `key` — `std::string`.
- **Returns:** `std::optional<std::string>` — the value, or `std::nullopt`
  if the key does not exist.

#### `ConfigurationManager::getValue(key, defaultValue)`
Looks up a value with a fallback.
- **In:** `key` — `std::string`; `defaultValue` — returned when the key is missing.
- **Returns:** `std::string` — the value or the default.

#### `ConfigurationManager::getAll()`
- **Returns:** `const std::unordered_map<std::string, std::string>&` — all
  key-value pairs (read-only view into the manager).

#### `ConfigurationManager::getAllKeys()`
- **Returns:** `std::vector<std::string>` — every key.

#### `ConfigurationManager::size()`
- **Returns:** `size_t` — the number of loaded key-value pairs.

#### `ConfigurationManager::clear()`
Removes every key-value pair.
- **Returns:** nothing.

#### `ConfigurationManager::setValue(key, value)`
Sets (or overwrites) one key-value pair programmatically — handy for
overriding file values at runtime.
- **In:** `key`, `value` — `std::string` each.
- **Returns:** nothing.

## Quick start

```cpp
#include "ConfigurationManager.hpp"

ConfigurationManager::ConfigurationManager config;
if (config.loadFromFile("config.cfg") != 0) {
    // 0 = success, -1 = file could not be opened
}

std::string host = config.getValue("host", "127.0.0.1");
int port = std::stoi(config.getValue("port", "5555"));
if (config.keyExists("debug_mode")) { /* ... */ }
config.setValue("debug_mode", "true");   // programmatic override
```

Example `config.cfg`:

```
# network settings
host: 127.0.0.1
port: 6000
debug_mode: false
```

## Building the library

### Static build
- `cmake -B build_static -G "MinGW Makefiles"`
- `cmake --build build_static`

### Dynamic build
- `cmake -B build_shared -G "MinGW Makefiles" -DBUILD_SHARED_LIBS=ON`
- `cmake --build build_shared`

## Building tests

### Static library test
- `g++ -std=c++17 tests/test_config.cpp -Iinclude -Lbuild_static -lConfigurationManager -o tests/test_config.exe`

### Dynamic library test
- `g++ -std=c++17 tests/test_config.cpp -Iinclude -DCONFIGURATIONMANAGER_DYNAMIC -Lbuild_shared -lConfigurationManager -o tests/test_config_dynamic.exe`
