@echo off
if not exist build (
    mkdir build
)

echo Compilando...
g++ test.cpp src\*.cpp -Iinclude -Iinclude\sqlitedatabasehandler -Iasio\include -DASIO_STANDALONE -D_WIN32_WINNT=0x0601 -std=c++17 -o .\build\test.exe -L.\lib -lsqlite3 -lws2_32 -lmswsock

if %errorlevel% neq 0 (
    echo.
    echo Fallo en la compilacion.
    exit /b %errorlevel%
) else (
    echo.
    echo Compilacion exitosa. Ejecutable en build\test.exe
)

pause
