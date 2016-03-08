#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>

// http://www.glfw.org/docs/latest/quick.html

// GLFWの関数呼出しが失敗した場合に呼び出されるcallback
// この例は単純に標準エラー出力にエラーを呼び出すcallback
void error_callback(int error, const char* description)
{
  fputs(description, stderr);
}

// インプットイベントを受け取る
// キーpushとreleaseのイベントを受け取る設定
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(int argc, char *argv[])
{
  // callback関数はセットされることでGLFWはそれをよびだすことができる
  // エラーcallback関数は、初期化前に呼び出せる数少ないGLFW関数の中の1つです
  // 初期化時にエラーになってもエラーの通知がされます
  glfwSetErrorCallback(error_callback);

  // GLFW libraryの初期化
  // 初期化に失敗したらEXIT_FAILUREが返ります
  if (!glfwInit())
    exit(EXIT_FAILURE);

  // windowとそのcontextの作成
  // https://www.opengl.org/wiki/OpenGL_Context
  // http://miffysora.wikidot.com/rendering-context
  // windowとcontextが混ざったオブジェクトを返す
  // http://www.glfw.org/docs/latest/group__window.html#ga5c336fddf2cbb5b92f65f10fb6043344
  // windowとcontextの生成が失敗したらNULLを返す
  GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  // OpenGLのAPIを使う前に必ず現在のOpenGLのcontextを保持しておかなければならない
  // このcontextは、別のcontextを作るまで残る、もしくは現在のcontextをもっているwindowが削除されるまで残る
  glfwMakeContextCurrent(window);

  // GLFWのwindowはダブルバッファリングを行っている
  // http://e-words.jp/w/%E3%83%80%E3%83%96%E3%83%AB%E3%83%90%E3%83%83%E3%83%95%E3%82%A1%E3%83%AA%E3%83%B3%E3%82%B0.html
  // 
  glfwSwapInterval(1);

  // windowに対するキーcallbackの設定
  glfwSetKeyCallback(window, key_callback);

  // それぞれのwindowはクローズしたかのフラグをもっている
  // ユーザーがwindowをクローズしようとしたらクローズフラグが立ちます。
  // フラグがたっただけではクローズされず、クローズフラグを監視して、このフラグがたったらwindowを自分で削除してください
  // glfwSetWindowCloseCallbackはクローズフラグがたったら即座に呼びだされます
  // glfwSetWindowShouldCloseは、自分自身でクローズフラグを立てることができます。
  // glfwWindowShouldCloseは、エスケープキーの押下によるwindowクローズを行いたいときに便利です
  while (!glfwWindowShouldClose(window))
  {
    float ratio;
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    ratio = width / (float) height;
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
    glBegin(GL_TRIANGLES);
    glColor3f(1.f, 0.f, 0.f);
    glVertex3f(-0.6f, -0.4f, 0.f);
    glColor3f(0.f, 1.f, 0.f);
    glVertex3f(0.6f, -0.4f, 0.f);
    glColor3f(0.f, 0.f, 1.f);
    glVertex3f(0.f, 0.6f, 0.f);
    glEnd();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // windowが要らなくなった消す
  // windowはこれ以上イベントを飛ばさなくなる
  glfwDestroyWindow(window);
  // applicationを終了する直前にGLFWをterminateする必要がある
  // 残っているwindowの削除やGLFWで確保したリソースを全て開放します
  // glfwTerminate()を呼びだした後にGLFWの関数を呼び出す場合は再度初期化が必要になります
  glfwTerminate();
  return 0;
}
