#include <SimulationHandler.h>

int main(){
    
    SimulationHandler* simHandle = SimulationHandler::instance();
    simHandle->run();

    return 0;
}