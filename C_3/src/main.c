#include <stdio.h>
#include <stdbool.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <KHR/khrplatform.h> // idfk what this is for i dont use it yet

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const unsigned int WINDOW_HEIGHT = 600;
const unsigned int WINDOW_WIDTH = 800;


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void triangle(void) {   // Function to render a triangle 
    float vertices[] = {    // Array of verticies
       -0.5f,  -0.5f,  0.0f,
        0.5f,  -0.5f,  0.0f,
        0.0f,   0.5f,  0.0f
    };
    unsigned int VBO;   // Create vertex buffer object
    glGenBuffers(1, &VBO);  // Assign VBO an id
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
};  


int main(void) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);    // Telling the window that its using vers. 4.6
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);    // idk why i need to do this tbh
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "beans", NULL, NULL);
    
    if (window == NULL) {   // Error for if it doesnt work
        printf("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {  // Another error for if it doesnt work
        printf("Failed to initialize GLAD");                    // but in a different way
        return -1;
    }    



    while(!glfwWindowShouldClose(window)) { // Render loop
        
        processInput(window);

        glClearColor(0.2, 0.3, 0.3, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        triangle();

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }


    glfwTerminate();

    return 0;
}