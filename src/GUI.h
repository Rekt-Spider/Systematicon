#pragma once
#include <vector>
#include <variant>
#include <include/Shader.h>
#include <include/Window.h>
#include <include/Camera.h>
#include <libs/imgui/imgui.h>
#include <libs/backends/imgui_impl_glfw.h>
#include <libs/backends/imgui_impl_opengl3.h>


enum GUI_ELEMENT_STATES{
    GUI_ELEMENT_TEST,
    GUI_ELEMENT_DEMO
};
enum ShaderProgram{
    ShaderProgram_Default,
    ShaderProgram_2D,
    ShaderProgram_3D
};
class GUI
{
public:
    static GUI* instance();
    GLFWwindow* getWindow();
    static std::vector<bool> getElementStates();
    static bool getElementState(GUI_ELEMENT_STATES element);
    static void setElementState(GUI_ELEMENT_STATES element, bool value);
    static Camera* getCamera();
private:
    //GUI state variables
    static std::vector<bool> elementStates;
    /* inter-package state variables */
    std::vector<std::variant<bool, float, int>> settings  = {
        /*PAUSE*/                false,
        /*LOCALIZED_VIEW*/       false,
        /*SIM_SPEED*/            1.00f,
        /*ZOOM*/                 1.00f,
        /*ENGINE_TYPE*/          false,
        /*ENSEMPLE_MODE*/        false,
        /*CONCURRENCY_MODE*/     false,
        /*HIDE_GUI*/             false
    };
    std::vector<Shader*> shaders;
    static Window* window;
    static GUI* theInstance;
    static Camera* camera;
    //may want to add multi-window support in the future
    GUI(unsigned int width = 1280U, unsigned int height = 720U);  // Private constructor
    ~GUI();
    void setShaders(const char* vertPath, const char* fragPath);
    Shader* getShader(ShaderProgram program);
    void updateMVPMatrix();
    void processInput(GLFWwindow* win);
    void setup();
    void render();
    void cleanup();
    void setElementStates(std::vector<bool> states);
    
    
   
};
