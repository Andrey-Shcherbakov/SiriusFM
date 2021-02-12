#include "IRProviderConst.h"
#include "DiffusionGBM.h"
#include "MCEngine1D.hpp"

using namespace SiriusFM;
using namespace std;

int test1(int argc, char * argv[]){
    if(argc != 7){
        std::cerr << "PARAMS: mu, sigma, s0, T_days, tau_min, P" << std::endl;
        return 1;
    }

    double mu = atof(argv[1]);
    double sigma = atof(argv[2]);
    double s0 = atof(argv[3]);
    long T_days = atol(argv[4]);
    int tau_min = atoi(argv[5]);
    long P = atol(argv[6]);

    if(mu <= 0 || sigma <= 0 || s0 <= 0 || T_days <= 0 || tau_min <= 0 || P <= 0){
        std::cerr << "mu <= 0 || sigma <= 0 || s0 <= 0 || T_days <= 0 || tau_min <= 0 || P <= 0" << std::endl;
        return 2;
    }

    CcyE ccyA = CcyE::USD;
    IRProvider<IRModeE::Const> irp(nullptr);
    DiffusionGBM diff(mu, sigma);

    MCEngine1D <decltype(diff), decltype(irp), decltype(irp),
                decltype(ccyA), decltype(ccyA)>
    mce(20'000, 20'000); //400 m

    time_t t0 = time(nullptr);
    time_t T = t0 + T_days * 86400;
    double Ty = double(T_days) / 365.25;
    //Run MC
    mce.Simulate<false>(t0, T, tau_min, s0, P, &diff, &irp, &irp, ccyA, ccyA);

    //Analyse the results
    auto res = mce.GetPaths();
    long L1 = get<0>(res);
    long P1 = get<1>(res);
    double const *paths = get<2>(res);

    //Compute E (expexted value) of Log st
    double EST  = 0.0;
    double EST2 = 0.0;
    int NVP = 0; //Valid Paths
    for(int p = 0; p < P1; ++p){
        double const *path = paths + p * L1;
        double ST = path[L1 - 1];
        //In practice may get ST < 0
        if (ST <= 0) continue;
        ++NVP;

        double RT = log(ST/s0);
        EST += RT; EST2 += RT * RT;
    } //End of p Loop

    assert(NVP > 0);
    EST /= double (NVP); //mu - sigma^2/2

    //Now find variation of ST
    double VarST = (EST2 - double (NVP) * EST * EST) / double(NVP - 1); //sigma^2T
    double sigma2E = VarST / Ty;
    double muE = (EST + VarST/2.0) / Ty;

    cout << "mu = " << mu << "muE =" << muE << endl;
    cout << "sigma2 = " << sigma * sigma << "sigma2E =" << sigma2E << endl;

    return 0;
};
