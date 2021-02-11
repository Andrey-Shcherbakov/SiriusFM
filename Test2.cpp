#include "IRProviderConst.h"
#include "DiffusionGBM.h"
#include "MCEngine1D.hpp"
#include "VanillaOption.h"

using namespace siriusFM;
using namespace std;

int test2(int argc, char * argv[]){
    if(argc != 9){
        std::cerr << "PARAMS: mu, sigma, s0, Call/Put, K, T_days, tau_min, P" << std::endl;
        return 1;
    }

    double mu = atof(argv[1]);
    double sigma = atof(argv[2]);
    double s0 = atof(argv[3]);
    char const * opt_type = argv[4];
    double K = atof(argv[5]);
    long T_days = atol(argv[6]);
    int tau_min = atoi(argv[7]);
    long P = atol(argv[8]);

    if(mu < 0 || sigma <= 0 || s0 <= 0 || T_days <= 0 || tau_min <= 0 || P <= 0){
        std::cerr << "mu < 0 || sigma <= 0 || s0 <= 0 || T_days <= 0 || tau_min <= 0 || P <= 0" << std::endl;
        return 2;
    }

    Option const * option;
    if(strcmp(opt_type, "Call") == 0){
        option = new EurCallOption(K, T_days);
    }
    else if(strcmp(opt_type, "Put") == 0) {
        option = new EurPutOption(K, T_days);
    }
    else throw std::invalid_argument("There is no such Option type");

    CcyE ccyA = CcyE::USD;
    IRProvider<IRModeE::Const> irp("IRFile.txt");
    DiffusionGBM diff(mu, sigma);

    MCEngine1D <decltype(diff), decltype(irp), decltype(irp),
                decltype(ccyA), decltype(ccyA)>
    mce(20'000, 20'000); //400 m

    time_t t0 = time(nullptr);
    time_t T = t0 + T_days * 86400;
    double Ty = double(T_days) / 365.25;
    //Run MC Risk neutral
    mce.Simulate<true>(t0, T, tau_min, s0, P, &diff, &irp, &irp, ccyA, ccyA);

    //Analyse the results
    auto res = mce.GetPaths();
    long L1 = get<0>(res);
    long P1 = get<1>(res);
    double const *paths = get<2>(res);

    //Compute E (expexted value) of Log st
    double EST  = 0.0;
    //double EST2 = 0.0;
    //int NVP = 0; //Valid Paths
    for(int p = 0; p < P1; ++p){
        double const *path = paths + p * L1;
        /*double ST = path[L1 - 1];
        //In practice may get ST < 0
        if (ST <= 0) continue;*/
        //++NVP;

        double Payoff = option->payoff(L1, nullptr, path);
        //std::cout << "Payoff = " << Payoff << '\n';
        EST += Payoff;
        /*double RT = log(ST/s0);
        EST += RT; EST2 += RT * RT;*/
    } //End of p Loop

    //assert(NVP > 0);
    EST /= double (P1); //mu - sigma^2/2
    EST *= exp((-1)*irp.r(ccyA, 0)*Ty);
    //Now find variation of ST
    /*double VarST = (EST2 - double (NVP) * EST * EST) / double(NVP - 1); //sigma^2T
    double sigma2E = VarST / Ty;
    double muE = (EST + VarST/2.0) / Ty;

    cout << "mu = " << mu << "muE =" << muE << endl;
    cout << "sigma2 = " << sigma * sigma << "sigma2E =" << sigma2E << endl;*/

    cout << "Option price = " << EST << endl;

    return 0;
};

int main(int argc, char * argv[]){
    test2(argc, argv);
    return 0;
}
