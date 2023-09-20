// OpenGL Triangle Demo Project
// Create To Learn The Basics Of The OpenGL API
// Ryan Lim Jing Xiang - 2023

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <cstdio>
#include <stdexcept>

const char *g_Title = "OpenGL Triangle";
const unsigned int g_Width = 1280;
const unsigned int g_Height = 720;

// Triangle Vertices
const float vertices[] = {
    -0.5f,
    -0.5f,
    0.0f,
    0.5f,
    -0.5f,
    0.0f,
    0.0f,
    0.5f,
    0.0f,
};

// Vertex Shader Source Code
const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 wPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(wPos.x, wPos.y, wPos.z, 1.0);\n"
                                 "}\0";

// Fragment Shader Source Code
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 fragmentColour;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   fragmentColour = vec4(0.0, 0.5, 1.0, 1.0);\n"
                                   "}\0";

int main()
{
    printf("OpenGL Triangle Demo Project\nCreate To Learn The Basics Of The OpenGL API\nRyan Lim Jing Xiang - 2023\n");
    try
    {
        // Create The Window
        GLFWwindow *window = nullptr;
        {
            if (!glfwInit())
            {
                throw std::runtime_error("Failed to Initialise GLFW.");
            }

            // Hint To GLFW Out OpenGL Version
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            // WINDOW!
            window = glfwCreateWindow(g_Width, g_Height, g_Title, nullptr, nullptr);
            glfwMakeContextCurrent(window); // Set The OpenGL Context To This Window

            // Validate The Window Has Been Created Successfully
            if (!window)
            {
                glfwDestroyWindow(window);
                glfwTerminate();
                throw std::runtime_error("Window Creation Failed.");
                return -1;
            }

            // Shows The Window!
            glfwShowWindow(window);
        }

        // Initiate OpenGL
        unsigned int shaderProgram = 0;
        unsigned int VAO = 0;
        unsigned int VBO = 0;
        {
            // Load OpenGL function using GLAD
            if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                glfwDestroyWindow(window);
                glfwTerminate();
                throw std::runtime_error("Failed to Initialise GLAD.");
                return -1;
            }

            // Set The Viewport Equal To Our Window Dimensions
            glViewport(0, 0, g_Width, g_Height);

            // Create the Vertex Buffer
            {
                glGenBuffers(1, &VBO); // Allocate A Vertex Buffer Object Using OpenGL.
                glBindBuffer(GL_ARRAY_BUFFER, VBO);
                glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

                // Generate A Vertex Array Object To Bind The Pipeline
                glGenVertexArrays(1, &VAO);
                glBindVertexArray(VAO);

                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void *)0);
                glEnableVertexAttribArray(0);
            }

            // Create The Shader Program
            {
                int success = 0;
                char errorLog[512];

                // Load The Vertex Shader
                unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
                glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
                glCompileShader(vertexShader);

                // Check That The Vertex Shader Compiled Properly
                glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
                if (!success)
                {
                    glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
                    glfwDestroyWindow(window);
                    glfwTerminate();
                    throw std::runtime_error(errorLog);
                    return -1;
                }

                // Load The Fragment Shader
                unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
                glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
                glCompileShader(fragmentShader);

                // Check That The Fragment Shader Compiled Properly
                glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
                if (!success)
                {
                    glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
                    glfwDestroyWindow(window);
                    glfwTerminate();
                    throw std::runtime_error(errorLog);
                    return -1;
                }

                // Link The Shader Program
                shaderProgram = glCreateProgram();
                glAttachShader(shaderProgram, vertexShader);
                glAttachShader(shaderProgram, fragmentShader);
                glLinkProgram(shaderProgram);

                // Check That The Shader Program Linked Properly
                glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
                if (!success)
                {
                    glGetShaderInfoLog(shaderProgram, 512, NULL, errorLog);
                    glfwDestroyWindow(window);
                    glfwTerminate();
                    throw std::runtime_error(errorLog);
                    return -1;
                }

                // The Shader Program Has Been Linked, So Delete The Shader Blobs.
                glDeleteShader(fragmentShader);
                glDeleteShader(vertexShader);
            }
        }

        // Application Loop
        {
            while (!glfwWindowShouldClose(window))
            {
                // Poll Events
                glfwPollEvents();

                // Update

                // Render
                glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
                glClear(GL_COLOR_BUFFER_BIT);

                glUseProgram(shaderProgram);
                glBindVertexArray(VAO);

                glDrawArrays(GL_TRIANGLES, 0, 3);

                glfwSwapBuffers(window);
            }
        }

        // Clean Up
        {
            glfwDestroyWindow(window);
            glfwTerminate();
        }
    }
    catch (const std::exception &e)
    {
        printf("Error: %s\n", e.what());
    }

    return 0;
}