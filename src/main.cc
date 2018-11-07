#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "circle_evader.h"

namespace {

const int WINDOW_SIZE = 600;

void error_callback(const int error, const char* description) {
  std::cerr << "GLFW Error: " << description << std::endl;
}

} // namespace

int main() {
  // Seed for random number generator: rand(). To be done once.
  srand(time(NULL));

  glfwSetErrorCallback(error_callback);

  if (!glfwInit()) {
    std::cout << "GLFW failed to initialize. Exiting" << std::endl;
    exit(EXIT_FAILURE);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  GLFWwindow* window = glfwCreateWindow(WINDOW_SIZE, WINDOW_SIZE, "Circle Evader", NULL, NULL);
  if (!window) {
    std::cout << "GLFW failed to create a window. Exiting" << std::endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(window);

  glewExperimental = GL_TRUE;
  glewInit();
  std::cout << "Using OpenGL version: " << glGetString(GL_VERSION) << std::endl;

  CircleEvader game{15, WINDOW_SIZE};
  game.startup();

  double mousex, mousey;

  while (!glfwWindowShouldClose(window)) {
    glfwGetCursorPos(window, &mousex, &mousey);
    game.update(glfwGetTime(), mousex, mousey);
    game.render(glfwGetTime());

    if (game.is_game_over()) { break; }

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  game.shutdown();
  glfwTerminate();

  exit(EXIT_SUCCESS);
}
