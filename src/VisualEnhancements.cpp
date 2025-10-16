#include "../include/VisualEnhancements.h"
#include <iostream>

VisualEnhancements::VisualEnhancements(GameMemory* gameMemory, Config* config) 
    : gameMemory(gameMemory), config(config), overlayDC(nullptr), overlayWindow(nullptr), crosshairEnabled(true) {
    
    crosshairSettings.size = config->GetInt("crosshair_size", 10);
    crosshairSettings.thickness = config->GetInt("crosshair_thickness", 2);
    crosshairSettings.gap = config->GetInt("crosshair_gap", 3);
    crosshairSettings.color = RGB(0, 255, 0);
    crosshairSettings.outline = config->GetBool("crosshair_outline", true);
    crosshairSettings.outlineColor = RGB(0, 0, 0);
    crosshairSettings.dot = config->GetBool("crosshair_dot", false);
    
    std::cout << "🎨 Visual Enhancements initialized\n";
}

VisualEnhancements::~VisualEnhancements() { Cleanup(); }

void VisualEnhancements::Update() {
    if (!gameMemory || !gameMemory->IsProcessRunning()) return;
    if (crosshairEnabled && config->GetBool("crosshair_enabled", true)) {
        DrawCrosshair();
    }
}

bool VisualEnhancements::Initialize() { return true; }
void VisualEnhancements::Cleanup() { /* Placeholder */ }

void VisualEnhancements::SetCrosshairEnabled(bool enabled) {
    crosshairEnabled = enabled;
    std::cout << "🎯 Custom crosshair " << (enabled ? "enabled" : "disabled") << "\n";
}

bool VisualEnhancements::IsCrosshairEnabled() const {
    return crosshairEnabled;
}

void VisualEnhancements::DrawCrosshair() {
    int centerX, centerY;
    GetScreenCenter(centerX, centerY);
    // Placeholder crosshair drawing
}

void VisualEnhancements::DrawCrosshairLine(int x1, int y1, int x2, int y2) { /* Placeholder */ }
void VisualEnhancements::DrawCrosshairDot(int x, int y) { /* Placeholder */ }

void VisualEnhancements::GetScreenCenter(int& centerX, int& centerY) {
    int screenWidth, screenHeight;
    GetScreenDimensions(screenWidth, screenHeight);
    centerX = screenWidth / 2;
    centerY = screenHeight / 2;
}

void VisualEnhancements::GetScreenDimensions(int& width, int& height) {
    width = GetSystemMetrics(SM_CXSCREEN);
    height = GetSystemMetrics(SM_CYSCREEN);
}