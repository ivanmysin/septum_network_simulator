#ifndef PAC_NEURON_H
#define PAC_NEURON_H
#include"FS_neuron.h"

class Pac_neuron : public FS_neuron
{
    public:
        Pac_neuron(const vector<double>&);
        virtual ~Pac_neuron();
        void integrate (double dt, double duraction);
    protected:
        double gbarKS;
        double gbarH;

        double gKS;
        double gH;

        double Eh;

        double H;
        double p;
        double q;
    private:

        double H_integrate(double dt);
        double p_integrate(double dt);
        double q_integrate(double dt);
};

#endif // PAC_NEURON_H

