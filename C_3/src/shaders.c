#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "shaders.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

char *readShader(const char  *path) {
    FILE *file = fopen(path, "rb");
    
    if (file == NULL) {
        printf("FAILED TO READ FILE\n");
        return "";
    }
    
    fseek(file, 0, SEEK_END);
    unsigned int length = ftell(file);
    fclose(file);

    file = fopen(path, "r");
    char *shaderString = malloc(length);
    fread(shaderString, 1, length, file);
    fclose(file);

    shaderString[length] = '\0';
    
    return shaderString;
}

void compileShader(unsigned int shader, const char *path) {
    char *shaderSource = readShader(path);
    glShaderSource(shader, 1, &shaderSource, NULL);
    free(shaderSource);
    glCompileShader(shader);
}

unsigned int createShaderProgram(const char *vertPath, const char *fragPath) {
    unsigned int vertShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragShader = glCreateShader(GL_FRAGMENT_SHADER);

    int success = false;
    char log[2048];

    compileShader(vertShader, vertPath);
    compileShader(fragShader, fragPath);

    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertShader, 512, NULL, log);
        printf("ERROR! VERTEX SHADER FAILED TO COMPILE!\n");
        printf(log);
    }

    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragShader, 512, NULL, log);
        printf("ERROR! FRAGMENT SHADER FAILED TO COMPILE!\n");
        printf(log);
    }

    unsigned int shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertShader);
    glAttachShader(shaderProgram, fragShader);
    int fragTexLocation = glGetUniformLocation(shaderProgram, "ourTexture");
    glUseProgram(shaderProgram);
    glUniform4f(fragTexLocation, 0.0, 0.0, 0.0, 0.0);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, log);
        printf("ERROR! SHADER PROGRAM FAILED TO LINK!\n");
        printf(log);
    }

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    return shaderProgram;
}
