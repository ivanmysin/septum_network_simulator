#include "Network.h"

Network::Network(Properties* npr,  Properties* syns)
{
    n = npr->getN();
    neurons = new FS_neuron* [n]; // set array of neurons
    for (int i=0; i<n; i++) {
        if (npr->param[i].size()<12) {
            neurons[i] = new FS_neuron(npr->param[i]);
        } else {
            neurons[i] = new Pac_neuron(npr->param[i]);
        }
    }

    numberSynapses = syns->getN(); // set array of synapses
    synapses = new Synapse* [numberSynapses];
    for (int i=0; i<numberSynapses; i++) {
        int pre_ind = (int)syns->param[i][0];
        int post_ind = (int)syns->param[i][1];
        synapses[i] = new Synapse (neurons[pre_ind], neurons[post_ind], syns->param[i]);
    }


}
////////////////////////////////////////////////////////////////
Network::~Network()
{
    for (int i=0; i<n; i++) {
        delete neurons[i];
    }
    delete [] neurons;
    for (int i=0; i<numberSynapses; i++) {
        delete synapses[i];
    }
    delete [] synapses;
}
////////////////////////////////////////////////////////////////
// intergrate model
void Network::integrate (double dt, double duraction)
{

    double t=0;
    while (t < duraction) {
        for (int i=0; i<n; i++) { // integrate all neurins by one time step
            neurons[i]->integrate(dt, dt);
            neurons[i]->checkFired(t);
        }

        for (int i=0; i<numberSynapses; i++) { // integrate all synapses by one time step
            synapses[i]->integrate(dt, dt);
        }

        t+=dt;
    }
}
//////////////////////////////////////////////////////
// save raster of activity in csv file
void Network::saveRaster (const char* file)
{
    ofstream outfile;
    outfile.open(file);
    for (int i=0; i<n; i++) {
        vector<double> sp = neurons[i]->getFiring();
        int len = sp.size();
        for (int j=0; j<len; j++) {
            outfile << i+1 << ", " << sp[j] << "\n";
        }
    }

    outfile.close();
}
//////////////////////////////////////////////////
// return times in sec of spikes of neuron by its index
vector <double> Network::getContiniousFiring (int neuronInd, double dt, double duraction)
{
    int len = duraction/dt;
    vector <double> firing = neurons[neuronInd]->getFiring();
    vector <double> signal(len, 0);
    for (unsigned int i=0; i<firing.size(); i++) {
        int indTmp = firing[i]/dt;
        signal[indTmp] = 1;
    }
    return signal;
}
///////////////////////////////////////////////////////
