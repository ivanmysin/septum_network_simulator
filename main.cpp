#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>

#include "FS_neuron.h"
#include "Pac_neuron.h"
#include "Synapse.h"
#include "Network.h"
#include "Sim_Parameters.h"
#include "parser_function.h"

using namespace std;

int main(int argc, char* argv[])
{

    char* descriptionModelFile; // file with description of model
    char defaultFile[25] = {'n','e','t','w','o','r','k','_','d','e','s','c','r','i','p','t','i','o','n','.','t','x','t','\0'};
    if (argc<2) {
        // if description file is not defined
        // set to deault
        descriptionModelFile = &defaultFile[0];
    } else {
        descriptionModelFile = argv[1];
    }

    string simDescription = read_txt_file (descriptionModelFile); // read content of file with description of model
    string sim = delete_comments (simDescription);                // delete comments



    Properties npr;  // declare object of neurons params
    npr.findProperties("Neurons_start:", "Neurons_end", sim); // find properies on neurons from string

    Properties syns; // declare object of synapses params
    syns.findProperties("Synapses_start:", "Synapses_end", sim);


    Simparametrs simpr; // declare oblect of simulation params
    simpr.findParameters("Simulation_parameters_start:", "Simulation_parameters_end", sim);


    Network septum(&npr, &syns); // declare network object

    septum.integrate(simpr.getDt(), simpr.getDuraction()); // integrate model with dt and duraction parameters

    if (argc > 2) {
        // if file for saving raster defined
        // save data to it
        septum.saveRaster(argv[2]);
    } else {
        // else save data to file with same directory as descrioption with name "Raster.csv"
        int len = strlen(descriptionModelFile);
        char* outfile = new char [len + 12];
        rasterFile(outfile, descriptionModelFile, "Raster.csv");
        septum.saveRaster(outfile);
    }

    cout << endl << "Calculation is finished!" << endl;
    return 0;
}



