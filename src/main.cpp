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
            glfwMakeContextCurrent(window);         // Set The OpenGL Context To This Window

            // Validate The Window Has Been Created Successfully
            if (!window)
            {
                glfwTerminate();
                throw std::runtime_error("Window Creation Failed.");
                return -1;
            }

            // Shows The Window!
            glfwShowWindow(window);

        }

        // Application Loop
        {
            while (!glfwWindowShouldClose(window))
            {
                // Poll Events
                glfwPollEvents();
                // Update

                // Render
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