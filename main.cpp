#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main()
{
    GLFWwindow* window;
    //Initialize the library
    if( !glfwInit() )
    {
        std::cerr<<"Failed to initialize GLFW"<<std::endl;
        return -1;
    }
    //Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(600, 600, "Window Title", nullptr,nullptr);
    if( window == nullptr )
    {
        glfwTerminate();
        return -1;
    }
    //Make the window's context current
    glfwMakeContextCurrent(window);
    //Loop until the user closes the window

    // Initialize GLEW
     if (glewInit() != GLEW_OK)
     {
     std::cerr<<"Failed to initialize GLEW"<<std::endl;
     glfwTerminate();
     return -1;
     }
    // Dark blue background
    glClearColor(0.2f, 0.2f, 0.5f, 0.0f);
    std::vector<float> points = {
     0.0f, 0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     -0.5f, -0.5f, 0.0f
     };
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), &points[0], GL_STATIC_DRAW);
    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    //shaders
    const char* vertex_shader =
     "#version 400\n"
     "in vec3 vp;"
     "void main() {"
     " gl_Position = vec4(vp, 1.0);"
     "}";
     const char* fragment_shader =
     "#version 400\n"
     "out vec4 frag_color;"
     "void main() {"
     " frag_color = vec4(0.5, 0.0, 0.0, 1.0);"
     "}";
     GLuint vs =
     glCreateShader(GL_VERTEX_SHADER);
     glShaderSource(vs, 1, &vertex_shader, nullptr);
     glCompileShader(vs);

     GLuint fs =
     glCreateShader(GL_FRAGMENT_SHADER);
     glShaderSource(fs, 1, &fragment_shader, nullptr);
     glCompileShader(fs);
     GLuint shader_programme = glCreateProgram();
     glAttachShader(shader_programme, fs);
     glAttachShader(shader_programme, vs);
     glLinkProgram(shader_programme);
     glUseProgram(shader_programme);
     while(glfwWindowShouldClose(window) == 0 )
     {
        // Clear the screen.
        glClear( GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwPollEvents();
        glfwSwapBuffers(window);
     }
     // Close OpenGL window and terminate GLFW
     glfwTerminate();

     return 0;

}
