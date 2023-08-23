os=$(uname -s)

compile_for_macos(){
    rm fire
    gcc -o fire fire.c -framework GLUT -framework OpenGL -lm -Wno-deprecated-declarations
    ./fire
}
compile_for_ubuntu(){
    rm fire
    gcc -o fire fire.c -lGL -lGLU -lglut
    ./fire
}
if [ "$os" = "Darwin" ]; then
    compile_for_macos
elif [ "$os" = "Linux" ]; then
    compile_for_ubuntu
else
    echo "Unsupported operating system: $os"
fi