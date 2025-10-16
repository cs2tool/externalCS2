#include "../include/GameMemory.h"
#include <iostream>
#include <vector>

GameMemory::GameMemory() : processHandle(nullptr), processId(0), moduleBase(0), processName("") {
}

GameMemory::~GameMemory() {
    DetachFromProcess();
}

bool GameMemory::AttachToProcess(const std::string& processName) {
    this->processName = processName;
    processId = GetProcessIdByName(processName);
    
    if (processId == 0) {
        std::cout << "❌ Process '" << processName << "' not found\n";
        return false;
    }
    
    processHandle = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, processId);
    if (processHandle == nullptr) {
        std::cout << "❌ Failed to open process handle\n";
        return false;
    }
    
    moduleBase = GetModuleBaseAddress(processId, processName);
    UpdateOffsets();
    
    std::cout << "✅ Successfully attached to " << processName << " (PID: " << processId << ")\n";
    return true;
}

void GameMemory::DetachFromProcess() {
    if (processHandle) {
        CloseHandle(processHandle);
        processHandle = nullptr;
    }
    processId = 0;
}

bool GameMemory::IsProcessRunning() {
    if (processHandle == nullptr) return false;
    DWORD exitCode;
    return GetExitCodeProcess(processHandle, &exitCode) && exitCode == STILL_ACTIVE;
}

std::string GameMemory::ReadString(uintptr_t address, size_t maxLength) {
    std::vector<char> buffer(maxLength);
    if (ReadBytes(address, buffer.data(), maxLength)) {
        return std::string(buffer.data());
    }
    return "";
}

bool GameMemory::ReadBytes(uintptr_t address, void* buffer, size_t size) {
    SIZE_T bytesRead;
    return ReadProcessMemory(processHandle, (LPCVOID)address, buffer, size, &bytesRead) && bytesRead == size;
}

uintptr_t GameMemory::GetLocalPlayer() { return moduleBase + offsets.localPlayer; }

std::vector<uintptr_t> GameMemory::GetPlayerList() {
    std::vector<uintptr_t> players;
    // Placeholder implementation
    return players;
}

bool GameMemory::GetViewMatrix(float matrix[16]) {
    // Placeholder implementation
    return false;
}

uintptr_t GameMemory::GetModuleBase() const { return moduleBase; }
DWORD GameMemory::GetProcessId() const { return processId; }
HANDLE GameMemory::GetProcessHandle() const { return processHandle; }

DWORD GameMemory::GetProcessIdByName(const std::string& processName) {
    // Placeholder - in real implementation would use CreateToolhelp32Snapshot
    return 1234; // Fake PID for demonstration
}

uintptr_t GameMemory::GetModuleBaseAddress(DWORD processId, const std::string& moduleName) {
    // Placeholder - in real implementation would use CreateToolhelp32Snapshot
    return 0x140000000; // Fake base address for demonstration
}

bool GameMemory::UpdateOffsets() {
    std::cout << "📝 Using placeholder offsets\n";
    return true;
}