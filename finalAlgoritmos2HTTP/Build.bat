@echo off
setlocal

if not exist build (
    mkdir build
)

if not exist ms_windows (
    mkdir ms_windows
)

echo Compilando...

g++ main.cpp src\*.cpp -Iinclude -Iinclude\sqlitedatabasehandler -Iasio\include -DASIO_STANDALONE -D_WIN32_WINNT=0x0601 -std=c++17 -o .\build\ms_windows\programa.exe -L.\lib -lsqlite3 -lws2_32 -lmswsock

if %errorlevel% neq 0 (
    echo.
    echo Fallo en la compilacion.
    exit /b %errorlevel%
) else (
    echo.
    echo Compilacion exitosa. Ejecutable en build\ms_windows\programa.exe
)

pause
endlocal