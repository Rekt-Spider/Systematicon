#include <iostream>
#include <GUI.h>

enum Settings{
    PAUSE,
    LOCALIZED_VIEW,
    SIM_SPEED,
    ZOOM,
    ENGINE_TYPE,
    ENSEMPLE_MODE,
    CONCURRENCY_MODE,
    HIDE_GUI
};

class SimulationHandler
{
public:
    static SimulationHandler* instance();
    void run();
private:
    /* data */
    static SimulationHandler* theInstance;
    SimulationHandler();
    ~SimulationHandler();
};


