#include "../include/Config.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

// Static member definitions
const std::string Config::Keys::AIMBOT_ENABLED = "aimbot_enabled";
const std::string Config::Keys::AIMBOT_KEY = "aimbot_key";
const std::string Config::Keys::ESP_ENABLED = "esp_enabled";
const std::string Config::Keys::TRIGGER_ENABLED = "trigger_enabled";
const std::string Config::Keys::CROSSHAIR_ENABLED = "crosshair_enabled";

Config::Config() : configPath("") {
}

Config::~Config() {
}

bool Config::LoadConfig(const std::string& filePath) {
    configPath = filePath;
    std::ifstream file(filePath);
    if (!file.is_open()) {
        CreateDefaultConfig();
        return SaveConfig();
    }
    
    std::string line;
    while (std::getline(file, line)) {
        ParseLine(line);
    }
    file.close();
    return true;
}

bool Config::SaveConfig() {
    std::ofstream file(configPath);
    if (!file.is_open()) return false;
    
    for (const auto& pair : settings) {
        file << pair.first << "=" << pair.second << "\n";
    }
    file.close();
    return true;
}

void Config::CreateDefaultConfig() {
    SetBool("aimbot_enabled", true);
    SetInt("aimbot_key", VK_LBUTTON);
    SetBool("esp_enabled", true);
    SetBool("trigger_enabled", true);
    SetInt("trigger_key", VK_LMENU);
    SetBool("crosshair_enabled", true);
}

bool Config::GetBool(const std::string& key, bool defaultValue) {
    auto it = settings.find(key);
    return (it != settings.end()) ? (it->second == "true") : defaultValue;
}

int Config::GetInt(const std::string& key, int defaultValue) {
    auto it = settings.find(key);
    return (it != settings.end()) ? std::stoi(it->second) : defaultValue;
}

void Config::SetBool(const std::string& key, bool value) {
    settings[key] = value ? "true" : "false";
}

void Config::SetInt(const std::string& key, int value) {
    settings[key] = std::to_string(value);
}

float Config::GetFloat(const std::string& key, float defaultValue) {
    auto it = settings.find(key);
    return (it != settings.end()) ? std::stof(it->second) : defaultValue;
}

std::string Config::GetString(const std::string& key, const std::string& defaultValue) {
    auto it = settings.find(key);
    return (it != settings.end()) ? it->second : defaultValue;
}

int Config::GetKey(const std::string& key, int defaultValue) {
    return GetInt(key, defaultValue);
}

void Config::SetFloat(const std::string& key, float value) {
    settings[key] = std::to_string(value);
}

void Config::SetString(const std::string& key, const std::string& value) {
    settings[key] = value;
}

void Config::SetKey(const std::string& key, int keyCode) {
    SetInt(key, keyCode);
}

void Config::ParseLine(const std::string& line) {
    if (line.empty() || line[0] == '#' || line[0] == '[') return;
    size_t pos = line.find('=');
    if (pos != std::string::npos) {
        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);
        settings[key] = value;
    }
}

std::string Config::Trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t");
    if (start == std::string::npos) return "";
    size_t end = str.find_last_not_of(" \t");
    return str.substr(start, end - start + 1);
}

std::vector<std::string> Config::Split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}