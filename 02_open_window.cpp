#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>

void init(void)
{
  // バッファを初期化するカラー情報
  //           R     G    B    a
  glClearColor(0.0, 0.0, 1.0, 1.0);
}

int main(int arg, char *argv[])
{
  if (!glfwInit())
    exit(EXIT_FAILURE);

  // windowとそのcontextの作成
  GLFWwindow* window = glfwCreateWindow(640, 480, "Title", NULL, NULL);

  if (!window)
  {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  // OpenGLのAPIを使う前に必ず現在のOpenGLのcontextを保持しておかなければならない
  // OpenGLのAPIが必要なければいらない
  glfwMakeContextCurrent(window);

  init();

  while (!glfwWindowShouldClose(window))
  {
    // 画面を初期化
    // https://www.opengl.org/sdk/docs/man/html/glClear.xhtml
    // http://qiita.com/edo_m18/items/95483cabf50494f53bb5
    // ウィンドウを塗りつぶします. mask には塗りつぶすバッファを指定します
    // OpenGL が管理する画面上のバッファ (メモリ) には, 色を格納するカラーバッファの他, 
    // 隠面消去処理に使うデプスバッファ, 凝ったことをするときに使うステンシルバッファ, 
    // カラーバッファの上に重ねて表示されるオーバーレイバッファなど, いくつかのものがあり, 
    // これらが一つのウィンドウに重なって存在しています. 
    // mask に GL_COLOR_BUFFER_BIT を指定したときは, カラーバッファだけが塗りつぶされます.
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    // マウスやキー入力のイベントはこの関数で監視する。
    // 待ちになっているイベントを処理する
    // これがないとくるくる回っている
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}


