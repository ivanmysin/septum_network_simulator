#ifndef SYNAPSE_H
#define SYNAPSE_H
#include <iostream>
#include <math.h>
#include <vector>
#include "FS_neuron.h"

using namespace std;


class Synapse
{
    public:
        Synapse(FS_neuron* pre_, FS_neuron* post_, const vector <double>&);
        void setSynapseProperies(char type, double w_, FS_neuron* pre_, FS_neuron* post_);
        void integrate (double dt, double duraction);
        virtual ~Synapse();

    protected:
    private:
        // param of synapse
        double teta;
        double K;
        double alpha_s;
        double beta_s;
        double Erev;
        double gbarS;
        double S;
        double w;
        FS_neuron* pre; // presynaptic neuron
        FS_neuron* post; // post synaptic neuron
        double Isyn;
};

#endif // SYNAPSE_H

