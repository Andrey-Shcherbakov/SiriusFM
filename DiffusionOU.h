#pragma once
#include <iostream>

//en.cppreference.com

namespace siriusFM{
	class DiffusionOU{
		private:
			double const m_cappa;
			double const m_sigma;
			double const m_theta;
		public:
			double mu(doubles a_s, double t) const{
				return m_cappa * (m_theta - a_s);
			}

			double sigma(doubles a_s, double t) const{
				if(a_s < 0) return 0.0; //return((a_s < 0) ? 0 : m_sigma * a_s);
				return m_sigma * a_s;
			}
			DiffusionOU(double a_cappa, double a_sigma, double a_theta)
			: m_cappa(a_cappa)
			  m_sigma(a_sigma)
			  m_theta(a_theta){
				if(m_sigma <= 0) throw std::invalid_argument("...");
				if(m_cappa < 0)  throw std::invalid_argument("...");
			}
	};
}
