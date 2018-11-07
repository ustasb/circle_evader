#include <iostream>
#include <sstream>
#include <fstream>
#include "gl_helpers.h"

namespace {
  std::string load_source_from_file(const std::string& file_path) {
    std::ifstream source_file{file_path};

    if (!source_file.is_open()) {
      std::cout << "Could not find file:\n" << file_path << "\nExiting" << std::endl;
      exit(EXIT_FAILURE);
    }

    std::stringstream buffer;
    buffer << source_file.rdbuf();

    source_file.close();

    return buffer.str();
  }
}

GLuint load_shader_from_file(const std::string& file_path, const GLuint shader_type) {
  std::string source = load_source_from_file(file_path);
  const GLchar* shader_source = static_cast<const GLchar*>(source.c_str());
  // For some reason, this doesn't always work...:
  // const GLchar* shader_source = static_cast<const GLchar*>(load_source_from_file(file_path).c_str());

  GLuint shader = glCreateShader(shader_type);
  glShaderSource(shader, 1, &shader_source, NULL);
  glCompileShader(shader);

  GLint shader_status;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_status);
  if (shader_status != GL_TRUE) {
    std::cout << "The shader for:\n" << file_path << "\nfailed to compile. Exiting" << std::endl;
    exit(EXIT_FAILURE);
  }

  return shader;
}
