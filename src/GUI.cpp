#include <GUI.h>

Window* GUI::window = nullptr;
GUI* GUI::theInstance = nullptr;

GUI::GUI(unsigned int width, unsigned int height){
    GUI::window = new Window(width, height);
}
GUI* GUI::instance(){
    if(theInstance == nullptr){
        theInstance = new GUI();
    }
    return theInstance;
}
GUI::~GUI() {
    if(theInstance){
        delete GUI::window;
        window = nullptr;
        delete theInstance;
        theInstance = nullptr;
    }
}
GLFWwindow* GUI::getWindow(){
    return GUI::window->getWindow();
}
