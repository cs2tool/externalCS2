#pragma once
#include <Windows.h>
#include "GameMemory.h"
#include "Config.h"

class VisualEnhancements {
private:
    GameMemory* gameMemory;
    Config* config;
    HDC overlayDC;
    HWND overlayWindow;
    bool crosshairEnabled;

    struct CrosshairSettings {
        int size;
        int thickness;
        int gap;
        COLORREF color;
        bool outline;
        COLORREF outlineColor;
        bool dot;
    };

    CrosshairSettings crosshairSettings;

public:
    VisualEnhancements(GameMemory* gameMemory, Config* config);
    ~VisualEnhancements();

    void Update();
    bool Initialize();
    void Cleanup();

    // Crosshair functions
    void SetCrosshairEnabled(bool enabled);
    bool IsCrosshairEnabled() const;

private:
    void DrawCrosshair();
    void DrawCrosshairLine(int x1, int y1, int x2, int y2);
    void DrawCrosshairDot(int x, int y);
    
    // Screen utility functions
    void GetScreenCenter(int& centerX, int& centerY);
    void GetScreenDimensions(int& width, int& height);
};