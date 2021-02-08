#pragma once
#include <iostream>

//en.cppreference.com

namespace siriusFM{
	class DiffusionLipton{
		private:
			double const m_mu;
			double const m_sigma0;
			double const m_sigma1;
            double const m_sigma2;
		public:
			double mu(doubles a_s, double t){
				return m_mu * a_s;
			}

			double sigma(doubles a_s, double t){
				if(a_s < 0) return 0.0; //return((a_s < 0) ? 0 : m_sigma * a_s);
				return (m_sigma0 + m_sigma1 * a_s + m_sigma2 * std::pow(a_s, 2));
			}
			DiffusionLipton(double a_mu, double a_sigma0, double a_sigma1, double a_sigma2)
			: m_mu(a_mu)
			  m_sigma(a_sigma0)
			  m_sigma(a_sigma1)
              m_sigma(a_sigma2){
				if(m_sigma0 < 0) throw std::invalid_argument("...");
                if(m_sigma1 < 0) throw std::invalid_argument("...");
                if(m_sigma1*m_sigma1-4*m_sigma0*m_sigma2 >= 0) throw std::invalid_argument("...");
			}
	};
}
