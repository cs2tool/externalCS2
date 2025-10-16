#include <iostream>
#include <Windows.h>
#include <thread>
#include <chrono>
#include "include/AimBot.h"
#include "include/ESP.h"
#include "include/TriggerBot.h"
#include "include/VisualEnhancements.h"
#include "include/GameMemory.h"
#include "include/Config.h"

int main() {
    std::cout << "🎮 ExternalCS2 - Counter-Strike 2 External Tool\n";
    std::cout << "================================================\n";
    std::cout << "⚠️  Educational Purpose Only - Practice Windows API Programming\n\n";

    // Initialize configuration
    Config config;
    if (!config.LoadConfig("config.ini")) {
        std::cout << "⚠️  Config file not found, using defaults\n";
    }

    // Initialize game memory handler
    GameMemory gameMemory;
    if (!gameMemory.AttachToProcess("cs2.exe")) {
        std::cout << "❌ Failed to attach to CS2 process\n";
        std::cout << "Make sure Counter-Strike 2 is running and you have admin privileges\n";
        system("pause");
        return -1;
    }

    std::cout << "✅ Successfully attached to CS2 process\n";
    
    // Initialize components
    AimBot aimBot(&gameMemory, &config);
    ESP esp(&gameMemory, &config);
    TriggerBot triggerBot(&gameMemory, &config);
    VisualEnhancements visualEnhancements(&gameMemory, &config);

    std::cout << "🔄 Starting main loop...\n";
    std::cout << "Press ESC to exit\n\n";

    // Main loop
    bool running = true;
    while (running) {
        // Check for exit key
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            running = false;
            break;
        }

        // Update components
        aimBot.Update();
        esp.Update();
        triggerBot.Update();
        visualEnhancements.Update();

        // Sleep to prevent high CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    std::cout << "\n👋 Exiting ExternalCS2...\n";
    return 0;
}