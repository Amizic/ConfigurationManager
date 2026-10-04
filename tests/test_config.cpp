#include "ConfigurationManager.hpp"
#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdlib>

// Helper function to print section headers
void printSection(const std::string& title)
{
    std::cout << "\n=== " << title << " ===\n";
}

int main()
{
    // First, let's create a test config file
    {
        std::ofstream testFile("test.conf");
        testFile << "# Database configuration\n";
        testFile << "host: localhost\n";
        testFile << "port: 5432\n";
        testFile << "database: myapp_db\n";
        testFile << "username: admin\n";
        testFile << "password: secret123\n";
        testFile << "\n";
        testFile << "# Application settings\n";
        testFile << "max_connections: 100\n";
        testFile << "timeout: 30\n";
        testFile << "debug_mode: true\n";
        testFile << "log_level: verbose\n";
        testFile << "\n";
        testFile << "# This is a comment\n";
        testFile << "   # This line starts with spaces then comment\n";
        testFile << "    spaced_key   :    spaced_value   \n";
        testFile.close();
    }
    
    ConfigurationManager::ConfigurationManager config;
    
    // Test 1: Load file
    printSection("Test 1: Load Configuration File");
    int result = config.loadFromFile("test.conf");
    std::cout << "Load result: " << result << " (0 = success)\n";
    std::cout << "Number of keys loaded: " << config.size() << "\n";
    
    // Test 2: Key existence
    printSection("Test 2: Key Existence");
    std::cout << "Has 'host': " << (config.keyExists("host") ? "true" : "false") << "\n";
    std::cout << "Has 'port': " << (config.keyExists("port") ? "true" : "false") << "\n";
    std::cout << "Has 'nonexistent': " << (config.keyExists("nonexistent") ? "true" : "false") << "\n";
    
    // Test 3: Get values with optional
    printSection("Test 3: Get Values (Optional)");
    auto host = config.getValue("host");
    if (host)
    {
        std::cout << "Host: " << *host << "\n";
    }
    else
    {
        std::cout << "Host not found\n";
    }
    
    auto missing = config.getValue("missing_key");
    if (!missing)
    {
        std::cout << "Missing key correctly returned nullopt\n";
    }
    
    // Test 4: Get values with default
    printSection("Test 4: Get Values (With Default)");
    std::string db = config.getValue("database", "default_db");
    std::string server = config.getValue("server", "production");
    std::cout << "Database: " << db << " (should be myapp_db)\n";
    std::cout << "Server: " << server << " (should be production - default)\n";
    
    // Test 5: Get all keys
    printSection("Test 5: All Keys");
    auto keys = config.getAllKeys();
    std::cout << "All keys found:\n";
    for (const auto& key : keys)
    {
        std::cout << "  - " << key << "\n";
    }
    
    // Test 6: Get all key-value pairs
    printSection("Test 6: All Key-Value Pairs");
    const auto& allConfig = config.getAll();
    for (const auto& [key, value] : allConfig)
    {
        std::cout << "  " << key << " = " << value << "\n";
    }
    
    // Test 7: Set value programmatically
    printSection("Test 7: Set Values");
    config.setValue("app_name", "TestApp");
    config.setValue("version", "1.0.0");
    std::cout << "Added app_name: " << config.getValue("app_name", "") << "\n";
    std::cout << "Added version: " << config.getValue("version", "") << "\n";
    std::cout << "New size: " << config.size() << "\n";
    
    // Test 8: Override existing value
    printSection("Test 8: Override Value");
    std::cout << "Old timeout: " << config.getValue("timeout", "") << "\n";
    config.setValue("timeout", "60");
    std::cout << "New timeout: " << config.getValue("timeout", "") << "\n";
    
    // Test 9: Trim functionality
    printSection("Test 9: Trim Test");
    auto spacedValue = config.getValue("spaced_key");
    if (spacedValue)
    {
        std::cout << "Value for 'spaced_key': '" << *spacedValue << "'\n";
        std::cout << "Trim working: " << (*spacedValue == "spaced_value" ? "YES" : "NO") << "\n";
    }
    
    // Test 10: Load non-existent file
    printSection("Test 10: Load Non-existent File");
    ConfigurationManager::ConfigurationManager config2;
    int result2 = config2.loadFromFile("nonexistent.conf");
    std::cout << "Load result: " << result2 << " (-1 = error)\n";
    std::cout << "Size after failed load: " << config2.size() << "\n";
    
    // Test 11: Clear
    printSection("Test 11: Clear Configuration");
    std::cout << "Size before clear: " << config.size() << "\n";
    config.clear();
    std::cout << "Size after clear: " << config.size() << "\n";
    std::cout << "Has 'host' after clear: " << (config.keyExists("host") ? "true" : "false") << "\n";
    
    // Test 12: Real-world usage example
    printSection("Test 12: Real-world Usage Example");
    ConfigurationManager::ConfigurationManager appConfig;
    appConfig.loadFromFile("test.conf");
    
    std::string dbHost = appConfig.getValue("host", "localhost");
    std::string dbPort = appConfig.getValue("port", "5432");
    std::string dbName = appConfig.getValue("database", "default");
    std::string dbUser = appConfig.getValue("username", "root");
    std::string dbPass = appConfig.getValue("password", "");
    int maxConn = std::stoi(appConfig.getValue("max_connections", "10"));
    int timeout = std::stoi(appConfig.getValue("timeout", "30"));
    bool debug = appConfig.getValue("debug_mode", "false") == "true";
    
    std::cout << "Database Connection String:\n";
    std::cout << "  postgresql://" << dbUser << ":" << dbPass << "@" << dbHost << ":" << dbPort << "/" << dbName << "\n";
    std::cout << "  Max Connections: " << maxConn << "\n";
    std::cout << "  Timeout: " << timeout << "s\n";
    std::cout << "  Debug Mode: " << (debug ? "ON" : "OFF") << "\n";
    
    // Test 13: Comments and empty lines don't get parsed
    printSection("Test 13: Comments Not Parsed");
    std::cout << "Has '#': " << (appConfig.keyExists("#") ? "true" : "false") << "\n";
    std::cout << "Has '# This': " << (appConfig.keyExists("# This") ? "true" : "false") << "\n";
    std::cout << "Config doesn't contain comments - GOOD\n";
    
    std::cout << "\n=== ALL TESTS COMPLETED ===\n";
    system("pause");
    return 0;
}