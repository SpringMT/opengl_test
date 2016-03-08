## 春山のテスト
GLFW
http://www.glfw.org/

GLFWは、OpenGLを使ったアプリを書くためのシンプルなフレームワークです。

## install

brew install --static glfw3

## compile
clang hello_world.cpp -framework Cocoa -framework OpenGL -framework IOKit -framework CoreFoundation -framework CoreVideo -I/opt/boxen/homebrew/include -L/opt/boxen/homebrew/lib -lglfw3
