#include "Synapse.h"


Synapse::Synapse(FS_neuron* pre_, FS_neuron* post_, const vector <double>& params)
{
    pre = pre_;
    post = post_;
    Erev = params[2];
    gbarS = params[3];
    w = params[4];
    alpha_s = params[5];
    beta_s = params[6];
    teta = params[7];
    K = params[8];
    S = 0;
    Isyn = 0;
}

Synapse::~Synapse()
{
    //dtor
}

void Synapse::integrate(double dt, double duraction)
{
    double Vpre = pre -> getV(); // V of pre neuron
    if (Vpre < -30 && S<0.005) {
        S = 0;
        return;
    };
    double Vpost = post -> getV();
    double F = 1 / (1+exp(-(Vpre-teta)/K));
    double S_0 = alpha_s*F/(alpha_s*F + beta_s);
    double tau_s = 1/(alpha_s*F + beta_s);
    S = S_0 -(S_0 - S)*exp(-duraction/tau_s);
    Isyn = w*gbarS*S*(Vpost - Erev);
    post -> setIsyn(Isyn); // Isyn for post neuron
}
