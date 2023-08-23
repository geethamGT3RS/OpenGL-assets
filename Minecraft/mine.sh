os=$(uname -s)

compile_for_macos(){
    rm mine
    gcc -o mine mine.c -framework GLUT -framework OpenGL -lm -Wno-deprecated-declarations
    ./mine
}
compile_for_ubuntu(){
    rm mine
    gcc -o mine mine.c -lGL -lGLU -lglut
    ./mine
}
if [ "$os" = "Darwin" ]; then
    compile_for_macos
elif [ "$os" = "Linux" ]; then
    compile_for_ubuntu
else
    echo "Unsupported operating system: $os"
fi