#pragma once
#include <string>
#include <map>
#include <Windows.h>

class Config {
private:
    std::string configPath;
    std::map<std::string, std::string> settings;
    
public:
    Config();
    ~Config();

    // File operations
    bool LoadConfig(const std::string& filePath);
    bool SaveConfig();
    void CreateDefaultConfig();

    // Setting getters
    bool GetBool(const std::string& key, bool defaultValue = false);
    int GetInt(const std::string& key, int defaultValue = 0);
    float GetFloat(const std::string& key, float defaultValue = 0.0f);
    std::string GetString(const std::string& key, const std::string& defaultValue = "");
    int GetKey(const std::string& key, int defaultValue = VK_LBUTTON);

    // Setting setters
    void SetBool(const std::string& key, bool value);
    void SetInt(const std::string& key, int value);
    void SetFloat(const std::string& key, float value);
    void SetString(const std::string& key, const std::string& value);
    void SetKey(const std::string& key, int keyCode);

    // Default configuration keys
    struct Keys {
        static const std::string AIMBOT_ENABLED;
        static const std::string AIMBOT_KEY;
        static const std::string AIMBOT_SMOOTH;
        static const std::string AIMBOT_FOV;
        static const std::string AIMBOT_RECOIL_CONTROL;
        
        static const std::string ESP_ENABLED;
        static const std::string ESP_SKELETON;
        static const std::string ESP_BOXES;
        static const std::string ESP_HEALTH;
        static const std::string ESP_NAMES;
        static const std::string ESP_WEAPONS;
        static const std::string ESP_TEAM_CHECK;
        
        static const std::string TRIGGER_ENABLED;
        static const std::string TRIGGER_KEY;
        static const std::string TRIGGER_DELAY;
        
        static const std::string CROSSHAIR_ENABLED;
        static const std::string CROSSHAIR_SIZE;
        static const std::string CROSSHAIR_COLOR;
    };

private:
    void ParseLine(const std::string& line);
    std::string Trim(const std::string& str);
    std::vector<std::string> Split(const std::string& str, char delimiter);
};