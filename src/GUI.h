#pragma once
#include <include/Window.h>

class GUI
{
public:
    static GUI* instance();
    GLFWwindow* getWindow();
    
private:
    /* data */
    //may want to add multi-window support in the future
    GUI(unsigned int width = 1280U, unsigned int height = 720U);  // Private constructor
    static Window* window;
    static GUI* theInstance;
    ~GUI();
};
