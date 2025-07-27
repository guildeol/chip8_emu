prepare:
    @echo "Configuring the project..."
    @mkdir -p build &&  \
     cd build &&        \
     cmake ..

build target="all": prepare
    @echo "Building {{target}}"
    @cd build && make {{target}}
