#ifndef NETWORK_H
#define NETWORK_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string.h>
#include "FS_neuron.h"
#include "Synapse.h"
#include "Pac_neuron.h"
#include "Sim_Parameters.h"
using namespace std;

class Network
{
    public:
        Network(Properties* npr, Properties* syns);
        virtual ~Network();
        void integrate (double dt, double duraction);
        void saveRaster (const char*);
        vector <double>  getContiniousFiring (int neuronInd, double dt, double duraction);
        void saveMeanFiring (const char*, vector <int>, vector <int>, double, double);

    protected:
    private:
        int n; //number of neurons in model;
        int numberSynapses; //number of synapses in model
        FS_neuron** neurons; // neurons in model
        Synapse** synapses;  // synapses in model
};

#endif // NETWORK_H

