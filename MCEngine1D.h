#pragma once
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <ctime>

namespace SiriusFM{
    template <typename Diffusion,
              typename AProvider,
              typename BProvider,
              typename AssetClassA,
              typename AssetClassB,
              typename PathEvaluator>
    class MCEngine1D{
        private:

            long const m_MaxL;  //Max Path  length
            long const m_MaxPM; // Max Number of Stored
            double * const m_paths; // Stored Paths
            double * const m_ts;    // TimeLine

        public:

            MCEngine1D(long a_MaxL, long a_MaxPM)
            : m_MaxL (a_MaxL),
			  m_MaxPM(a_MaxPM),
              m_paths(new double[m_MaxL * m_MaxPM]),
              m_ts   (new double[m_MaxL]){
                  if(m_MaxL <= 0 || m_MaxPM <= 0) throw std::invalid_argument("Bad MaxL or MaxPM");

                  for(long l = 0; l < m_MaxL; ++l)
                  {
                     m_ts[l] = 0;
                     long lp = l * m_MaxPM;
                     for (long p = 0; p < m_MaxPM; ++p)
                        m_paths[lp + p] = 0;
                  }
            };

            ~MCEngine1D(){
                delete[] m_paths;
                delete[] m_ts;
            };

            template <bool IsRN> //risk neutral templatisation
            void Simulate(time_t a_t0, //Curr(pricing) time
                          time_t a_T,  //Expiration time
                          int    a_tau_min, //length of tau in minutes (time step)
                          long a_P, //path number (half)
                          bool a_useTimerSeed,
                          Diffusion const * a_diff,
                          AProvider   const * a_rateA,
                          BProvider   const * a_rateB,
                          AssetClassA a_assetA,
                          AssetClassB a_assetB,
                          PathEvaluator* a_pathEval);

             MCEngine1D (MCEngine1D const &) = delete;
             MCEngine1D & operator = (MCEngine1D const &) = delete;
    };
};
