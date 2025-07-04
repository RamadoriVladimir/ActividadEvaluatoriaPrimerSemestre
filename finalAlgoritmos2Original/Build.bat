@echo off
if not exist build (
    mkdir build
)

echo Compilando...

g++ main.cpp src\*.cpp -Iinclude -std=c++14 -o build\programa.exe

if %errorlevel% neq 0 (
    echo.
    echo Fallo en la compilacion.
    exit /b %errorlevel%
) else (
    echo.
    echo Compilacion exitosa. Ejecutable en build\programa.exe
)

pause
