#include "Pac_neuron.h"

Pac_neuron::Pac_neuron(const vector<double>& param):FS_neuron(param)
{
    Eh = param[10];
    gbarKS = param[11];
    gbarH = param [12];

    H = 1 / (1+exp((V+80)/10));
    p = 1 / (1+exp(-(V+34)/6.5));
    q = 1 / (1+exp((V+65)/6.6));

    gKS = gbarKS*p*q;
    gH = gbarH*H;
}

Pac_neuron::~Pac_neuron()
{

}
///////////////////////////////////////////////
double Pac_neuron::H_integrate(double dt)
{
    double H_0 = 1 / (1+exp((V+80)/10));
    double tau_H = (200/(exp((V+70)/20)+exp(-(V+70)/20)))+5;
    return H_0 - (H_0 - H)*exp(-dt/tau_H);
}
////////////////////////////////////////////////
double Pac_neuron::p_integrate(double dt)
{
    double p_0 = 1/(1+exp(-(V+34)/6.5));
    double tau_p = 6;
    return p_0 -(p_0 - p)*exp(-dt/tau_p);
}
////////////////////////////////////////////////
double Pac_neuron::q_integrate(double dt)
{
    double q_0 = 1/(1+exp((V+65)/6.6));
    double tau_q0 = 100;
    double tau_q = tau_q0 *(1+ (1/(1+exp(-(V+50)/6.8))));
    return q_0 -(q_0 -q)*exp(-dt/tau_q);
}
/////////////////////////////////////////////////
void Pac_neuron::integrate (double dt, double duraction)
{
    double t=0;
    int i=0;
    while (t < duraction) {

        V = V + dt*(-gNa*(V-ENa) - gK*(V-EK) - gl*(V-El) - gKS*(V - EK) - gH*(V - Eh) - Isyn + Iext);

        m = alpha_m() / (alpha_m() + beta_m());
        n = n_integrate(dt);
        h = h_integrate(dt);
        H = H_integrate(dt);
        p = p_integrate(dt);
        q = q_integrate(dt);

        gNa = gbarNa*m*m*m*h;
        gK = gbarK*n*n*n*n;

        gKS = gbarKS*p*q;
        gH = gbarH*H;
        Isyn = 0;

        Iext = (*normRand)(*generator);

        i++;
        t+=dt;
    }
}
