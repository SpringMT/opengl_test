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
  glFlush();
}

void resize(GLFWwindow* window, int w, int h)
{
  glViewport(0, 0, w, h);
  glLoadIdentity();
}

void mouse(GLFWwindow* window, int button, int action, int mods)
{
  switch (button) {
    case GLFW_MOUSE_BUTTON_LEFT:
      printf("left");
      break;
    case GLFW_MOUSE_BUTTON_MIDDLE:
      printf("middle");
      break;
    case GLFW_MOUSE_BUTTON_RIGHT:
      printf("right");
      break;
    default:
      break;
  }
  printf(" button is ");

  switch (action) {
    case GLFW_RELEASE:
      printf("up");
      break;
    case GLFW_PRESS:
      printf("down");
      break;
    default:
      break;
  }

  printf(" with ");
  switch (mods) {
    case GLFW_MOD_SHIFT:
      printf("shift");
      break;
    case GLFW_MOD_CONTROL:
      printf("control");
      break;
    case GLFW_MOD_ALT:
      printf("alt");
      break;
    case GLFW_MOD_SUPER:
      printf("super");
      break;
    default:
      break;
  }

  double x, y;
  glfwGetCursorPos(window, &x, &y);

  printf(" at (%f, %f)\n", x, y);
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
    draw();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}

