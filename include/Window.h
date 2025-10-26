#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


class Window
{
	
public:
	
	Window(unsigned int width, unsigned int height);
	~Window();
	int getWindowCreationSuccess();
	int getGLADSuccess();
	GLFWwindow* getWindow() const;
	unsigned int getWidth();
	unsigned int getHeight();

private:
	GLFWwindow* window;
	int gladLoad = 0, windowCreation = 0;
	unsigned int width = 1280, height = 720;

};
