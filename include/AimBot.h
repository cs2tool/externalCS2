#pragma once
#include <Windows.h>
#include "GameMemory.h"
#include "Config.h"

class AimBot {
private:
    GameMemory* gameMemory;
    Config* config;
    bool isActive;
    
    struct Vector3 {
        float x, y, z;
        Vector3() : x(0), y(0), z(0) {}
        Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
    };

    struct Player {
        Vector3 position;
        Vector3 headPosition;
        bool isVisible;
        bool isEnemy;
        int health;
    };

    // Recoil control system
    Vector3 lastRecoilOffset;
    bool recoilControlEnabled;

public:
    AimBot(GameMemory* gameMemory, Config* config);
    ~AimBot();

    void Update();
    void SetActive(bool active);
    bool IsActive() const;

private:
    bool IsKeyPressed();
    Player GetNearestTarget();
    bool IsTargetVisible(const Player& target);
    Vector3 CalculateAimAngles(const Vector3& from, const Vector3& to);
    void ApplyRecoilControl();
    void SmoothAim(const Vector3& targetAngles);
    bool IsValidTarget(const Player& target);
};