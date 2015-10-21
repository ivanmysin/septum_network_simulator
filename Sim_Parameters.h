#ifndef SIM_PARAMETERS_H_INCLUDED
#define SIM_PARAMETERS_H_INCLUDED
#include <vector>
#include <iostream>

using namespace std;

class Properties
{
    public:
    vector <double>* param;
    Properties(){}
    /////////////////////////////
    ~Properties() {
        delete[] param;
    }
    /////////////////////////////
    void createParamN() {
        param = new vector <double> [N];
    };
    /////////////////////////////
    void deleteParamN() {
        delete [] param;
    }
    /////////////////////////////
    void printProperties() {
        for (int i=0; i<N; i++) {
            for (int j=0; j<(int)param[i].size(); j++) {
                cout << param[i][j] << ' ';
            }
            cout << endl;
        }
    }
    /////////////////////////////
    void setN(int n_) {N=n_;}
    /////////////////////////////
    int getN(){return N;}
    /////////////////////////////
    //void setParam(vector <double>*);
    void findProperties(const string& start, const string& end, const string& sim)
    {

        int startSection = sim.find(start);
        int endSection = sim.find(end);
        string section = sim.substr(startSection+start.size(), endSection-startSection-start.size()); // description of neuron



        int n=0; // number of elemets (neurons or synspses)
        for (int i=0; i<(int)section.size(); i++) {
            if (section[i] == ';') {
                n++;
            }
        }

        N = n;
        this -> createParamN();


    // find properties of each elemet in section

        int len = section.size();
        int neuronNumber=0;
        string oneParam;
        for (int cnt=0; cnt<len; cnt++) {
            switch (section[cnt]) {
                case (';'): {
                    const char* p = oneParam.c_str();
                    double value = atof(p);
                    this->param[neuronNumber].push_back(value);
                    neuronNumber++;
                    oneParam.clear();
                    break;
                }
                case (','): {
                    const char* p = oneParam.c_str();
                    double value = atof(p);
                    this->param[neuronNumber].push_back(value);
                    oneParam.clear();
                    break;
                }
                default: {
                    oneParam+=section[cnt];
                }
            }
        }
    }
    /////////////////////////////
    private:
        int N; //number of elemets (neurons or synapses)

};

class Simparametrs
{
    public:
        void findParameters(const string& start, const string& end, const string& sim)
        {
            int startSection = sim.find(start);
            int endSection = sim.find(end);
            string section = sim.substr(startSection+start.size(), endSection-startSection-start.size());
            {
                int dtInd = section.find("dt=");
                dtInd+=3;
                string dtChars;
                for (int i=dtInd; section[i]!=';'; i++) {
                    dtChars+=section[i];
                }
                const char* dtChar = dtChars.c_str();
                dt = atof(dtChar);
            }
            /////////////////////////////////////////////////////
            {
                int durInd = section.find("duraction=");
                durInd+=10;
                string durChars;
                for (int i=durInd; section[i]!=';'; i++) {
                    durChars+=section[i];
                }
                const char* durChar = durChars.c_str();
                duraction = atof(durChar);
            }
        }
        ////////////////////////////////////////
        double getDt() {return dt;}
        double getDuraction() {return duraction;}
    private:
        double dt;
        double duraction;
};

#endif // SIM_PARAMETERS_H_INCLUDED
