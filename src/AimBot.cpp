#include "../include/AimBot.h"
#include <iostream>

AimBot::AimBot(GameMemory* gameMemory, Config* config) 
    : gameMemory(gameMemory), config(config), isActive(false), recoilControlEnabled(true) {
    lastRecoilOffset = Vector3(0, 0, 0);
    std::cout << "🎯 AimBot initialized\n";
}

AimBot::~AimBot() {}

void AimBot::Update() {
    if (!gameMemory || !gameMemory->IsProcessRunning()) return;
    
    bool keyPressed = IsKeyPressed();
    if (keyPressed != isActive) {
        SetActive(keyPressed);
        std::cout << "🎯 AimBot " << (keyPressed ? "activated" : "deactivated") << "\n";
    }
}

void AimBot::SetActive(bool active) { isActive = active; }
bool AimBot::IsActive() const { return isActive; }

bool AimBot::IsKeyPressed() {
    int key = config->GetKey("aimbot_key", VK_LBUTTON);
    return (GetAsyncKeyState(key) & 0x8000) != 0;
}

AimBot::Player AimBot::GetNearestTarget() {
    Player target;
    target.position = Vector3(100, 100, 100);
    target.headPosition = Vector3(100, 100, 120);
    target.isVisible = true;
    target.isEnemy = true;
    target.health = 100;
    return target;
}

bool AimBot::IsTargetVisible(const Player& target) { return target.isVisible; }

AimBot::Vector3 AimBot::CalculateAimAngles(const Vector3& from, const Vector3& to) {
    return Vector3(0, 0, 0); // Placeholder
}

void AimBot::ApplyRecoilControl() { /* Placeholder */ }
void AimBot::SmoothAim(const Vector3& targetAngles) { /* Placeholder */ }

bool AimBot::IsValidTarget(const Player& target) {
    return target.isEnemy && target.health > 0 && IsTargetVisible(target);
}