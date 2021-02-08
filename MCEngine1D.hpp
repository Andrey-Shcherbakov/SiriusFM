#pragma once
#include "MCEngine1D.h"
#include "Time.h"
#include <random>
#include <cassert>

namespace siriusFM{
    template <typename Diffusion1D, typename AProvider,
              typename BProvider,   typename AssetClassA, typename AssetClassB>
    void MCEngine1D <Diffusion1D, AProvider,
                     BProvider,   AssetClassA, AssetClassB>
    ::Simulate(time_t a_t0,
               time_t a_T,
               int    a_tau_min,
               double a_s0,
               long a_P,
               Diffusion1D const * a_diff,
               AProvider   const * a_rateA,
               BProvider   const * a_rateB,
               AssetClassA a_A,
               AssetClassB a_B,
               bool a_isRN)
    {
        //check variables
        assert(a_diff != nullptr && a_rateA != nullptr && a_rateB != nullptr &&
               a_A != AssetClassA::UNDEFINED && a_B != AssetClassB::UNDEFINED &&
               a_t0 <= a_T && a_tau_min > 0 && a_P > 0);

        double y0 = YearFrac(a_t0);
        double yT = YearFrac(a_T);
        double tau = double(a_tau_min)/(365.25*1440.0);
        long L = (ceil((yT - y0)/tau)) + 1; //Path length
        long P = 2 * a_P; //Antithletic variables
        double stau = sqrt(tau);
        double tlast = yT - y0 - double(L-2) * tau;
        double slast = sqrt(tlast); //the duration of last interval may differ from tau

        if(L * P > m_MaxL * m_MaxP) throw std::invalid_argument("L * P > m_MaxL * m_MaxP");
        assert(slast <= stau && 0 < slast);

        std::normal_distribution <> N01(0.0, 1.0);
        std::mt19937_64 U;

        //Main Simulation Loop
        for(long p = 0; p < a_P; ++p){
            double * path0 = m_paths + 2 * p * L;
            double * path1 = m_paths + L;
            path0[0] = a_s0;
            path1[0] = a_s0;

            double y = y0; double sp0 = a_s0; double sp1 = a_s0;

            for(long l = 1; l < L; ++l){
                //Compute the trend and volatility
                double mu0 = 0.0; double mu1 = 0.0;
                if(a_isRN){
                    double delta_r = a_rateB->r(a_B, y) -
                                     a_rateA->r(a_A, y);
                    mu0 = delta_r + sp0;
                    mu1 = delta_r + sp1;
                }
                else{
                    mu0 = a_diff->mu(sp0, y);
                    mu1 = a_diff->mu(sp1, y);
                }
                double sigma0 = a_diff->sigma(sp0, y);
                double sigma1 = a_diff->sigma(sp1, y);

                double Z = N01(U);
                double sn0, sn1;
                if(l == L-1){
                    sn0 = sp0 + mu0 * tlast + sigma0 * Z * slast;
                    sn1 = sp1 + mu1 * tlast - sigma1 * Z * slast;
                    y += tlast;
                }
                else{
                    sn0 = sp0 + mu0 * tau + sigma0 * Z * stau;
                    sn1 = sp1 + mu1 * tau - sigma1 * Z * stau;
                    y += tau;
                }
                path0[l] = sn0;
                path1[l] = sn1;
                sp0 = sn0;
                sp1 = sn1;
            } //End of l Loop
        } //End of p Loop
    };
};