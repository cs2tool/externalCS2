@echo off
echo Building ExternalCS2...

REM Create directories
if not exist "obj" mkdir obj
if not exist "obj\src" mkdir obj\src
if not exist "bin" mkdir bin

REM Compile source files
echo Compiling source files...
g++ -std=c++17 -Wall -Iinclude -c main.cpp -o obj\main.o
g++ -std=c++17 -Wall -Iinclude -c src\AimBot.cpp -o obj\src\AimBot.o
g++ -std=c++17 -Wall -Iinclude -c src\ESP.cpp -o obj\src\ESP.o
g++ -std=c++17 -Wall -Iinclude -c src\TriggerBot.cpp -o obj\src\TriggerBot.o
g++ -std=c++17 -Wall -Iinclude -c src\VisualEnhancements.cpp -o obj\src\VisualEnhancements.o
g++ -std=c++17 -Wall -Iinclude -c src\GameMemory.cpp -o obj\src\GameMemory.o
g++ -std=c++17 -Wall -Iinclude -c src\Config.cpp -o obj\src\Config.o

REM Link executable
echo Linking executable...
g++ obj\main.o obj\src\*.o -o bin\ExternalCS2.exe -luser32 -lgdi32 -lkernel32

REM Copy config file
copy config.ini bin\

echo Build complete! Executable is in bin\ExternalCS2.exe
pause