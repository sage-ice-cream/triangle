#ifndef SHADER_H
#define SHADER_H

unsigned int createShaderProgram(const char*, const char*);

void setShaderInt(unsigned int, const char*, int);

void setShaderFloat(unsigned int, const char*, float);

#endif
