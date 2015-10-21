#ifndef FS_NEURON_H
#define FS_NEURON_H
#include <iostream>
#include <math.h>
#include <vector>
#include <random>
#include <chrono>
#include <string.h>
using namespace std;

class FS_neuron
{
    public:
        FS_neuron(const vector<double>&);
        virtual ~FS_neuron();
        double getV();
        virtual void integrate (double dt, double duraction);
        void setIsyn(double Isyn_) {Isyn += Isyn_;};
        double getIsyn() {return Isyn;};
        void setIext(double Iext_) {Iext = Iext_ ;};
        void checkFired(double t_);
        vector <double> getFiring(){return firing;};


    protected:
        double V; // Potential of neuron
        // reverse potentials
        double ENa;
        double EK;
        double El;
        // maximal condutance
        double gbarNa;
        double gbarK;
        // conductance
        double gl;
        double gNa;
        double gK;

        double fi;

        // gate variables
        double m;
        double h;
        double n;

        double Iext;     // external current

        double Iextmean; // mean of external current
        double variance; // variance of Iext for noise generation
        double Isyn;     // synaptic current

        vector <double> firing; // save times if firing
        bool countSp;
        double th; // threshod for spike detection


        default_random_engine* generator;
        normal_distribution<double>* normRand;

        // methods for intagrate gating variables
        double alpha_m();
        double beta_m();
        double alpha_h();
        double beta_h();
        double alpha_n();
        double beta_n();

        double h_integrate(double dt);
        double n_integrate(double dt);
};

#endif // FS_NEURON_H

