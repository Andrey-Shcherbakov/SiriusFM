#pragma once
#include <iostream>

//en.cppreference.com

namespace SiriusFM{
	class DiffusionCEV{
		private:
			double const m_mu;
			double const m_sigma;
			double const m_beta;
			double const m_s0;
		public:
			double mu(doubles a_s, double t) const{
				return m_mu * a_s;
			}

			double sigma(doubles a_s, double t) const{
				if(a_s < 0) return 0.0; //return((a_s < 0) ? 0 : m_sigma * a_s);
				return m_sigma * std::pow(a_s, m_beta);
			}
			DiffusionCEV(double a_mu, double a_sigma, double a_beta, double a_s0)
			: m_mu(a_mu),
			  m_sigma(a_sigma),
			  m_beta(a_beta),
			  m_s0(a_s0){
				if(m_sigma <= 0) throw std::invalid_argument("...");
				if(m_beta < 0) 	 throw std::invalid_argument("...");
			}
			double GetStartPoint() const{
				return m_s0;
			}
	};
}
