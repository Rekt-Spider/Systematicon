#include <GUI.h>
Window* GUI::window = nullptr;
GUI* GUI::theInstance = nullptr;
std::vector<bool> GUI::elementStates = std::vector<bool>(2, true);
Camera* GUI::camera = nullptr;
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


//TO-DO: create struct for neater management of Camera state variables
bool firstMouse = true;
float fov = 45;
float yaw = -90.0f;
float pitch = 0.0f;
float lastX = 1280.0f / 2.0f;
float lastY = 720.0f / 2.0f;
glm::mat4 model, view, projection;
//variables for standardizing camera movement speed
float deltaTime = 0.0f;
float lastFrame = 0.0f;
int fps;

GUI::GUI(unsigned int width, unsigned int height){
    
    GUI::window = new Window(width, height);
    GUI::camera = new Camera(glm::vec3(0.0f, 0.0f, 5.0f));;
    std::cout <<"Setting up application..." << std::endl;
    setup();
    std::cout <<"Finished setup, rendering..." << std::endl;
    render();
    std::cout << "Rendering terminated, cleaning up..." << std::endl;
    cleanup();
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
        delete GUI::theInstance;
        theInstance = nullptr;
        delete GUI::camera;
        camera = nullptr;
    }
}
GLFWwindow* GUI::getWindow(){
    return GUI::window->Window::getWindow();
}
void GUI::setShaders(const char* vertPath, const char* fragPath){
    Shader* shaderProgram = new Shader(vertPath, fragPath);
    shaders.push_back(shaderProgram);
}
void GUI::processInput(GLFWwindow* win){
    if(glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(win, true);
    }
    //camera movement
    if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS)
    camera->ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS)
    camera->ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS)
    camera->ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS)
    camera->ProcessKeyboard(RIGHT, deltaTime);
    //toggle GLFW_CURSOR
    if(glfwGetKey(win, GLFW_KEY_SLASH) == GLFW_PRESS){
        if(glfwGetInputMode(win, GLFW_CURSOR) == GLFW_CURSOR_NORMAL){
            glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        else{
            glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }
}
void GUI::setup(){
    glfwSetCursorPosCallback(getWindow(), mouse_callback);
    glfwSetScrollCallback(getWindow(), scroll_callback);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(GUI::getWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::StyleColorsDark();
    
}
void GUI::updateMVPMatrix(){
    view = camera->GetViewMatrix();
    model = glm::mat4(1.0f);
    //example model position
    glm::vec3 helloTriPos = glm::vec3(0.0f,0.0f,-5.0f);
    model = glm::translate(model, helloTriPos);
    projection = glm::perspective(glm::radians(camera->Fov), (float) window->getWidth() / (float) window->getHeight(), 0.1f, 1000.0f);
    Shader* workingShader = shaders.front();
    workingShader->setMat4("view", view);
    workingShader->setMat4("model", model);
    workingShader->setMat4("projection", projection);
}
void GUI::render(){
    //ImGui window state variables
    bool opened_Test = getElementState(GUI_ELEMENT_DEMO);
    bool opened_Demo = getElementState(GUI_ELEMENT_TEST);
    //compile & link shaders
    setShaders("../src/resources/vScene.vert", 
        "../src/resources/fScene.frag");
        //temp vertex data for a "Hello Triangle"
        float triVerts[] = {
            0.5f, -0.5f, 0.0f,   // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            0.0f,  0.5f, 0.0f,  // top
        };
        
    //initialize VBOs and VAOs for models in the scene
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triVerts), triVerts, GL_STATIC_DRAW);
        
    //set models' attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);
        
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;
    GLFWwindow* window = getWindow();
    while(!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        float cameraSpeed = deltaTime * 2.5f;
        glfwPollEvents();
        
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        if(!io.WantCaptureMouse && !io.WantCaptureKeyboard){
            processInput(window);
        }
        
        if(opened_Test){
            ImGui::Begin("Test", &opened_Test, ImGuiWindowFlags_NoCollapse);
            ImGui::Text("This works.");
            if(ImGui::Button("Close")){
                opened_Test = false;
            }
            ImGui::End();
        }
        //second window state variables
        int current = 0;
        const char* settings[] = {"Localized View", "Pause", "Save"};
        //Second window with elements
            
        if(opened_Demo){
            ImGui::Begin("Simulation Settings", &opened_Demo);
            ImGui::Combo("Settings", &current, settings, IM_ARRAYSIZE(settings));
            if(ImGui::Button("Close")){
                opened_Demo = false;
            }
            ImGui::End();
        }
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45, 0.45, 0.45, 1.00);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
        shaders.front()->use();
        updateMVPMatrix();

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
            
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); 
            
           
        glfwSwapBuffers(window);
    }
}

void GUI::cleanup(){
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
std::vector<bool> GUI::getElementStates(){
    return elementStates;
}
bool GUI::getElementState(GUI_ELEMENT_STATES element){
    return elementStates.at(element);
}
void GUI::setElementState(GUI_ELEMENT_STATES element, bool value){
    elementStates.at(element) = value;
}
Shader* GUI::getShader(ShaderProgram program){
    return shaders.at(program);
}
Camera* GUI::getCamera(){
    return camera;
}
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn){
    //do not move camera when ImGui elements are clickable
    if(glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL) return;
    
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;

        return;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;
    GUI::getCamera()->ProcessMouseMovement(xoffset, yoffset);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    GUI::getCamera()->ProcessMouseScroll(static_cast<float>(yoffset));
}
