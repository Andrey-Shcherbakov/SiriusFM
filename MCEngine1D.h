#pragma once
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <ctime>
#include <tuple>

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
            long m_L;
            long m_P;
        public:
            MCEngine1D(long a_MaxL, long a_MaxP)
            : m_MaxL(a_MaxL),
              m_MaxP(a_MaxP),
              m_paths(new double[m_MaxL * m_MaxP]),
              m_L(0),
              m_P(0){
                if(m_MaxL <= 0 || m_MaxP <= 0) throw std::invalid_argument("m_MaxL <= 0 || m_MaxP <= 0");
            };

            void Simulate(time_t a_t0, //Curr(pricing) time
                          time_t a_T,  //Expiration time
                          int    a_tau_min, //length of tau in minutes (time step)
                          double a_s0, //the starting point
                          long a_P, //path number (half)
                          Diffusion1D const * a_diff,
                          AProvider   const * a_rateA,
                          BProvider   const * a_rateB,
                          AssetClassA a_A,
                          AssetClassB a_B,
                          bool a_isRN //is risk-neutral flag
                          );
             ~MCEngine1D(){
                 delete[]m_paths;
             };
             std::tuple <long, long, double const *> GetPaths(){
                 return (m_L <= 0 || m_P <= 0) ? std::make_tuple(0, 0, nullptr)
                                               : std::make_tuple(m_L, m_P, m_paths);
             };
             MCEngine1D (MCEngine1D const &) = delete;
             MCEngine1D & operator = (MCEngine1D const &) = delete;
    };
};
