#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>

void init(void)
{
  glClearColor(0.0, 0.0, 1.0, 1.0);
}

int main(int arg, char* argv[])
{
  if (!glfwInit())
    exit(EXIT_FAILURE);

  // windowとそのcontextの作成
  GLFWwindow* window = glfwCreateWindow(480, 480, "Title", NULL, NULL);
  glfwMakeContextCurrent(window);

  init();

  if (!window)
  {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  while(!glfwWindowShouldClose(window))
  {
    glClear(GL_COLOR_BUFFER_BIT);

    // http://aidiary.hatenablog.com/entry/20080824/1281749722
    // http://www.wakayama-u.ac.jp/~tokoi/opengl/libglut.html#4
    glBegin(GL_QUADS);
    glVertex2d(-0.9, -0.9);
    glVertex2d( 0.9, -0.9);
    glVertex2d( 0.9,  0.9);
    glVertex2d(-0.9,  0.9);
    glEnd();
    glFlush();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}

