#pragma once
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <ctime>

namespace siriusFM{
    template <typename Diffusion1D,
              typename AProvider,
              typename BProvider,
              typename AssetClassA,
              typename AssetClassB>
    class MCEngine1D{
        private:
            long const m_MaxL; //Max Path length
            long const m_MaxP; //Max N Paths
            double * const m_paths; //data with out pathes for MC method
        public:
            MCEngine1D(long a_MaxL, long a_MaxP)
            : m_MaxL(a_MaxL),
              m_MaxP(a_MaxP),
              m_paths(new double[m_MaxL+m_MaxP]){
                if(m_MaxL <= 0 || m_MaxP <= 0) throw std::invalid_argument("m_MaxL <= 0 || m_MaxP <= 0");
            };

            void Simulate(time_t a_t0, //Curr(pricing) time
                          time_t a_T,  //Expiration time
                          int    a_tau_min, //length of tau in minutes (time step)
                          Diffusion1D const * a_diff,
                          AProvider   const * a_rateA,
                          BProvider   const * a_rateB,
                          AssetClassA a_A,
                          AssetClassB a_B,
                          bool a_isRN //is risk-neutral flag
                          );
    };
}
