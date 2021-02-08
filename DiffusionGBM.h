#pragma once
#include <iostream>

//en.cppreference.com

namespace siriusFM{
	class DiffusionGBM{
		private:
			double const m_mu;
			double const m_sigma;
		public:
			double mu(doubles a_s, double t){
				return m_mu * a_s;
			}

			double sigma(doubles a_s, double t){
				if(a_s < 0) return 0.0; //return((a_s < 0) ? 0 : m_sigma * a_s);
				return m_sigma * a_s;
			}
			DiffusionGBM(double a_mu, double a_sigma)
			: m_mu(s_mu)
			  m_sigma(a_sigma){
				if(m_sigma <= 0) throw std::invalid_argument("...");
			}
	};
}
