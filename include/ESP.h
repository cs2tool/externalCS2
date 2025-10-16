#pragma once
#include <Windows.h>
#include <vector>
#include <string>
#include "GameMemory.h"
#include "Config.h"

class ESP {
private:
    GameMemory* gameMemory;
    Config* config;
    HDC overlayDC;
    HWND overlayWindow;
    bool isInitialized;

    struct Player {
        float x, y, z; // World position
        int screenX, screenY; // Screen position
        int health;
        bool isVisible;
        bool isEnemy;
        bool isScoped;
        bool isFlashed;
        bool isShifting;
        bool isShiftingInScope;
        std::string name;
        std::string weapon;
    };

    struct BoneConnection {
        int from;
        int to;
    };

    std::vector<BoneConnection> skeletonBones;

public:
    ESP(GameMemory* gameMemory, Config* config);
    ~ESP();

    void Update();
    bool Initialize();
    void Cleanup();

private:
    void DrawPlayers();
    void DrawSkeleton(const Player& player);
    void DrawBox(const Player& player);
    void DrawHealthBar(const Player& player);
    void DrawName(const Player& player);
    void DrawWeapon(const Player& player);
    void DrawFlags(const Player& player);
    
    bool WorldToScreen(float worldX, float worldY, float worldZ, int& screenX, int& screenY);
    std::vector<Player> GetAllPlayers();
    COLORREF GetTeamColor(bool isEnemy);
    void SetupSkeletonBones();
    
    // Drawing helper functions
    void DrawLine(int x1, int y1, int x2, int y2, COLORREF color);
    void DrawRect(int x, int y, int width, int height, COLORREF color);
    void DrawText(int x, int y, const std::string& text, COLORREF color);
};