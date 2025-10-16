#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <vector>

class GameMemory {
private:
    HANDLE processHandle;
    DWORD processId;
    uintptr_t moduleBase;
    std::string processName;

    // CS2 Memory Offsets (placeholder values)
    struct Offsets {
        uintptr_t localPlayer = 0x1000000;
        uintptr_t entityList = 0x1000100;
        uintptr_t viewMatrix = 0x1000200;
        uintptr_t health = 0x100;
        uintptr_t position = 0x200;
        uintptr_t team = 0x300;
        uintptr_t bones = 0x400;
        uintptr_t weapon = 0x500;
        uintptr_t flags = 0x600;
    } offsets;

public:
    GameMemory();
    ~GameMemory();

    bool AttachToProcess(const std::string& processName);
    void DetachFromProcess();
    bool IsProcessRunning();

    // Memory reading functions
    template<typename T>
    T ReadMemory(uintptr_t address);
    
    template<typename T>
    bool WriteMemory(uintptr_t address, const T& value);

    std::string ReadString(uintptr_t address, size_t maxLength = 64);
    bool ReadBytes(uintptr_t address, void* buffer, size_t size);

    // Game-specific functions
    uintptr_t GetLocalPlayer();
    std::vector<uintptr_t> GetPlayerList();
    bool GetViewMatrix(float matrix[16]);
    
    // Utility functions
    uintptr_t GetModuleBase() const;
    DWORD GetProcessId() const;
    HANDLE GetProcessHandle() const;

private:
    DWORD GetProcessIdByName(const std::string& processName);
    uintptr_t GetModuleBaseAddress(DWORD processId, const std::string& moduleName);
    bool UpdateOffsets(); // Update memory offsets (would be needed for real implementation)
};

// Template implementations
template<typename T>
T GameMemory::ReadMemory(uintptr_t address) {
    T value = {};
    ReadProcessMemory(processHandle, (LPCVOID)address, &value, sizeof(T), nullptr);
    return value;
}

template<typename T>
bool GameMemory::WriteMemory(uintptr_t address, const T& value) {
    return WriteProcessMemory(processHandle, (LPVOID)address, &value, sizeof(T), nullptr);
}