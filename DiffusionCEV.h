#pragma once
#include <iostream>

//en.cppreference.com

namespace siriusFM{
	class DiffusionCEV{
		private:
			double const m_mu;
			double const m_sigma;
			double const m_beta
		public:
			double mu(doubles a_s, double t) const{
				return m_mu * a_s;
			}

			double sigma(doubles a_s, double t) const{
				if(a_s < 0) return 0.0; //return((a_s < 0) ? 0 : m_sigma * a_s);
				return m_sigma * std::pow(a_s, m_beta);
			}
			DiffusionCEV(double a_mu, double a_sigma, double a_beta)
			: m_mu(a_mu)
			  m_sigma(a_sigma)
			  m_beta(a_beta){
				if(m_sigma <= 0) throw std::invalid_argument("...");
				if(m_beta < 0) 	 throw std::invalid_argument("...");
			}
	};
}
