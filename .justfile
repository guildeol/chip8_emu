prepare:
    @echo "Configuring the project..."
    @mkdir -p build &&  \
     cd build &&        \
     cmake ..

build target="all": prepare
    @echo "Building {{target}}"
    @cd build && make {{target}}

clean:
    @echo "Cleaning the project..."
    @rm -rf build

test: prepare
    @echo "Running tests"
    @cd build && make chip8_test
    @./build/test/chip8_test
