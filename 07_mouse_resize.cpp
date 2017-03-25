#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

#include <iostream>
#include <cstdlib>
#include <string>

#define MAXPOINTS 100      /* 記憶する点の数 */
GLdouble point[MAXPOINTS][2]; /* 座標を記憶する配列 */
int pointnum = 0;          /* 記憶した座標の数 */

// GLFWの関数呼出しが失敗した場合に呼び出されるcallback
// この例は単純に標準エラー出力にエラーを呼び出すcallback
void error_callback(int error, const char* description)
{
  std::cerr << "glfwCreateWindow failed." << std::endl;
  fputs(description, stderr);
}

// インプットイベントを受け取る
// キーpushとreleaseのイベントを受け取る設定
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

void init(void)
{
  glClearColor(1.0, 1.0, 1.0, 1.0);
}

void draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
}

void resize(GLFWwindow* window, int w, int h)
{
  /* ウィンドウ全体をビューポートにする */
  glViewport(0, 0, w, h);
  /* 変換行列の初期化 */
  glLoadIdentity();
  /* スクリーン上の座標系をマウスの座標系に一致させる */
  glOrtho(-0.5, (GLdouble)w - 0.5, (GLdouble)h - 0.5, -0.5, -1.0, 1.0);
}

void mouse(GLFWwindow* window, int button, int action, int mods)
{
  static double x0, y0;
  double x, y;
  glfwGetCursorPos(window, &x, &y);

  switch (button) {
    case GLFW_MOUSE_BUTTON_LEFT:
      if (action == GLFW_RELEASE) {
        /* ボタンを押した位置から離した位置まで線を引く */
        // glColor3d()はこれから描画するものの色を指定します.
        glColor3d(1.0, 0.0, 0.0);
        // 2点を対にして, その間を直線で結びます
        glBegin(GL_LINES);
        glVertex2i(x0, y0);
        glVertex2i(x, y);
        glEnd();
        glFlush();
      }
      else {
        x0 = x;
        y0 = y;
      }
      break;
    case GLFW_MOUSE_BUTTON_MIDDLE:
      break;
    case GLFW_MOUSE_BUTTON_RIGHT:
      break;
    default:
      break;
  }
}

int main(int arg, char* argv[])
{
  glfwSetErrorCallback(error_callback);
  if (!glfwInit())
    exit(EXIT_FAILURE);

  // windowとそのcontextの作成
  GLFWwindow* window = glfwCreateWindow(320, 240, "Title", NULL, NULL);
  glfwSetWindowPos(window, 100, 100);
  glfwSetWindowSize(window, 320, 240);
  if (!window)
  {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);

  glfwSwapInterval(1);
  glfwSetKeyCallback(window, key_callback);
  glfwSetMouseButtonCallback(window, mouse);

  init();
  glfwSetWindowSizeCallback(window, resize);

  int width, height;
  glfwGetWindowSize(window, &width, &height);
  resize(window, width, height);

  while(!glfwWindowShouldClose(window))
  {
    //draw();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}

