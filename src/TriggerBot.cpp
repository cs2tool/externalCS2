#include "../include/TriggerBot.h"
#include <iostream>

TriggerBot::TriggerBot(GameMemory* gameMemory, Config* config) 
    : gameMemory(gameMemory), config(config), isActive(false), lastShotTime(0), shotDelay(100) {
    std::cout << "🔫 TriggerBot initialized\n";
}

TriggerBot::~TriggerBot() {}

void TriggerBot::Update() {
    if (!gameMemory || !gameMemory->IsProcessRunning()) return;
    
    bool keyPressed = IsKeyPressed();
    if (keyPressed != isActive) {
        SetActive(keyPressed);
        std::cout << "🔫 TriggerBot " << (keyPressed ? "activated" : "deactivated") << "\n";
    }

    if (isActive && config->GetBool("trigger_enabled", true)) {
        CrosshairTarget target = GetCrosshairTarget();
        if (ShouldShoot(target) && CanShoot()) {
            Shoot();
            lastShotTime = GetCurrentTime();
        }
    }
}

void TriggerBot::SetActive(bool active) { isActive = active; }
bool TriggerBot::IsActive() const { return isActive; }

bool TriggerBot::IsKeyPressed() {
    int key = config->GetKey("trigger_key", VK_LMENU);
    return (GetAsyncKeyState(key) & 0x8000) != 0;
}

TriggerBot::CrosshairTarget TriggerBot::GetCrosshairTarget() {
    CrosshairTarget target;
    target.isValid = true;
    target.isEnemy = true;
    target.health = 100;
    target.distance = 500.0f;
    return target;
}

bool TriggerBot::ShouldShoot(const CrosshairTarget& target) {
    return target.isValid && target.isEnemy && target.health > 0;
}

void TriggerBot::Shoot() {
    std::cout << "🔫 Shot fired!\n";
}

bool TriggerBot::CanShoot() {
    int delay = config->GetInt("trigger_delay", 100);
    return (GetCurrentTime() - lastShotTime) >= delay;
}

DWORD TriggerBot::GetCurrentTime() {
    return GetTickCount();
}