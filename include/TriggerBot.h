#pragma once
#include <Windows.h>
#include "GameMemory.h"
#include "Config.h"

class TriggerBot {
private:
    GameMemory* gameMemory;
    Config* config;
    bool isActive;
    DWORD lastShotTime;
    int shotDelay; // Delay between shots in milliseconds

    struct CrosshairTarget {
        bool isValid;
        bool isEnemy;
        int health;
        float distance;
    };

public:
    TriggerBot(GameMemory* gameMemory, Config* config);
    ~TriggerBot();

    void Update();
    void SetActive(bool active);
    bool IsActive() const;

private:
    bool IsKeyPressed();
    CrosshairTarget GetCrosshairTarget();
    bool ShouldShoot(const CrosshairTarget& target);
    void Shoot();
    bool CanShoot();
    
    // Utility functions
    DWORD GetCurrentTime();
};