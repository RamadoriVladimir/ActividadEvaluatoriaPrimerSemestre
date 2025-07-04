if [ ! -d "build" ]; then
    mkdir build
fi

if [ ! -d "build/gnu_linux" ]; then
    mkdir -p build/gnu_linux 
fi

echo "Compilando..."

g++ main.cpp src/*.cpp \
    -Iinclude \
    -Iinclude/sqlitedatabasehandler \
    -Ilibs/asio/include \
    -Ilibs/include \
    -std=c++17 \
    -o build/linux/programa \
    -L./lib \
    -lsqlite3

if [ $? -ne 0 ]; then
    echo ""
    echo "Fallo en la compilación."
    exit 1
else
    echo ""
    echo "Compilación exitosa. Ejecutable en build/linux/programa"
fi

read -p "Presiona Enter para continuar..."