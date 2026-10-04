#pragma once

#include <string>
#include <unordered_map>
#include <optional>
#include <vector>

#if defined(CONFIGURATIONMANAGER_DYNAMIC)
    #if defined(CONFIGURATIONMANAGER_BUILD)
        #define CONFIGURATIONMANAGER_API __declspec(dllexport)
    #else
        #define CONFIGURATIONMANAGER_API __declspec(dllimport)
    #endif
#else
    #define CONFIGURATIONMANAGER_API
#endif

namespace ConfigurationManager {

class CONFIGURATIONMANAGER_API ConfigurationManager
{
public:
    ConfigurationManager() = default;
    ~ConfigurationManager() = default;

    // Load configuration from file
    // Returns 0 on success, -1 if file cannot be opened
    int loadFromFile(const std::string& filePath);
    
    // Check if a key exists
    bool keyExists(const std::string& key) const;
    
    // Get value by key (returns std::nullopt if key doesn't exist)
    std::optional<std::string> getValue(const std::string& key) const;
    
    // Get value with default fallback
    std::string getValue(const std::string& key, const std::string& defaultValue) const;
    
    // Get all key-value pairs
    const std::unordered_map<std::string, std::string>& getAll() const;
    
    // Get all keys
    std::vector<std::string> getAllKeys() const;
    
    // Get number of loaded configurations
    size_t size() const;
    
    // Clear all configurations
    void clear();
    
    // Manually set a key-value pair
    void setValue(const std::string& key, const std::string& value);

private:
    static void trim(std::string& str);
    
    std::unordered_map<std::string, std::string> configMap;
};

} // namespace ConfigurationManager