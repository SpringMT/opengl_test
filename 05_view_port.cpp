#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

#include <iostream>
#include <cstdlib>
#include <string>

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
  glBegin(GL_POLYGON);
  glColor3d(1.0, 0.0, 0.0); /* 赤 */
  glVertex2d(-0.9, -0.9);
  glColor3d(0.0, 1.0, 0.0); /* 緑 */
  glVertex2d( 0.9, -0.9);
  glColor3d(0.0, 0.0, 1.0); /* 青 */
  glVertex2d( 0.9,  0.9);
  glColor3d(1.0, 1.0, 0.0); /* 黄 */
  glVertex2d(-0.9,  0.9);
  glEnd();
  glFlush();
}

void resize(GLFWwindow* window, int w, int h)
{
  glViewport(0, 0, w, h);
  glLoadIdentity();
  glOrtho(-w / 200.0, w / 200.0, -h / 200.0, h / 200.0, -1.0, 1.0);
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

  init();
  glfwSetWindowSizeCallback(window, resize);

  int width, height;
  glfwGetWindowSize(window, &width, &height);
  resize(window, width, height);

  while(!glfwWindowShouldClose(window))
  {
    draw();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}

