#include "FS_neuron.h"

FS_neuron::FS_neuron(const vector<double>& param)
{
    // set neuron params from vector
    V = param[0];
    ENa = param[1]; // mv Na reversal potential
    EK  = param[2]; // mv K reversal potential
    El  = param[3]; // mv Leakage reversal potential
    gbarNa = param[4]; // mS/cm^2 Na conductance
    gbarK  = param[5];  // mS/cm^2 K conductance
    gl = param[6];
    fi = param[7];
    Iextmean = param[8];
    variance = param[9];

    unsigned int seed = chrono::system_clock::now().time_since_epoch().count();
    generator =  new default_random_engine (seed);
    normRand = new normal_distribution <double> (Iextmean, variance);
    Iext = (*normRand)(*generator); // Iext generate from normal distribution

    m = alpha_m() / (alpha_m() + beta_m());
    n = alpha_n() / (alpha_n() + beta_n());
    h = alpha_h() / (alpha_h() + beta_h());

    gNa = gbarNa*m*m*m*h;
    gK = gbarK*n*n*n*n;

    Isyn = 0;
    countSp = true;
    th = -20;
}

FS_neuron::~FS_neuron()
{
    delete [] normRand;
    delete [] generator;
}

double FS_neuron::getV() {
    return V;
}
//////////////////////////////////////////////////
double FS_neuron::alpha_m()
{
    double alpha;
    double x = -0.1*(V+33);
    if (x == 0) {
        x = 0.000000001;
    }

    alpha = x/(exp(x)-1);
    return alpha;
}
//////////////////////////////////////////////////
double FS_neuron::beta_m()
{
    double beta = 4 *exp(-(V+58)/18);
    return beta;

}
//////////////////////////////////////////////////
double FS_neuron::alpha_h()
{
    double alpha = fi*0.07*exp(-(V+51)/10);
    return alpha;
}
//////////////////////////////////////////////////
double FS_neuron::beta_h()
{
    double beta = fi/(exp(-0.1*(V+21))+1);
    return beta;
}
/////////////////////////////////////////////////
double FS_neuron::alpha_n()
{
    double x = -0.1*(V+38);
    if ( x==0 ) {
        x = 0.00000000001;
    }
    double alpha = fi*0.1*x/(exp(x)-1);
    return alpha;
}
//////////////////////////////////////////////////
double FS_neuron::beta_n()
{
    return (fi*0.125* exp(-(V+48)/80));
}
///////////////////////////////////////////////////
double FS_neuron::h_integrate(double dt)
{
    double h_0 = alpha_h() / (alpha_h() + beta_h());
    double tau_h = 1 / (alpha_h() + beta_h());
    return h_0 -(h_0 - h)*exp(-dt/tau_h);
}

double FS_neuron::n_integrate(double dt)
{
    double n_0 = alpha_n() / (alpha_n() + beta_n());
    double tau_n = 1 / (alpha_n() + beta_n());
    return n_0 -(n_0 - n)*exp(-dt/tau_n);
}
///////////////////////////////////////////////////
void FS_neuron::integrate (double dt, double duraction)
{
    double t=0;
    int i=0;
    while (t < duraction) {

        V = V + dt*(gNa*(ENa - V) + gK*(EK - V) + gl*(El - V) - Isyn + Iext);

        m = alpha_m() / (alpha_m() + beta_m());
        n = n_integrate(dt);
        h = h_integrate(dt);
        gNa = gbarNa*m*m*m*h;
        gK = gbarK*n*n*n*n;

        Iext = (*normRand)(*generator);

        Isyn = 0;
        i++;
        t+=dt;
    }
}
//////////////////////////////////////////////////////
void FS_neuron::checkFired(double t_)
{
    if (V >= th && countSp) {
        firing.push_back(t_);
        countSp = false;
    }
    if (V < th) {
        countSp = true;
    }
}
//////////////////////////////////////////////////////

