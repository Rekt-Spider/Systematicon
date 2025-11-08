#include <SimulationHandler.h>
void run(){
    std::cout << "Running simulation..." << std::endl;
    GUI* gui = GUI::instance();
    while(!glfwWindowShouldClose(gui->getWindow()))
    {
        glfwSwapBuffers(gui->getWindow());
        glfwPollEvents();    
    }
}