#include <SimulationHandler.h>

SimulationHandler* SimulationHandler::theInstance = nullptr;

SimulationHandler::SimulationHandler(){
    
}

SimulationHandler::~SimulationHandler(){
   if(theInstance){
        delete SimulationHandler::theInstance;
        theInstance = nullptr;
   }
}

SimulationHandler* SimulationHandler::instance(){
    if(theInstance == nullptr){
        theInstance = new SimulationHandler();
    }
    return theInstance;
}


void SimulationHandler::run(){
    std::cout << "Running Systematicon..." << std::endl;
    GUI* gui = GUI::instance();
}