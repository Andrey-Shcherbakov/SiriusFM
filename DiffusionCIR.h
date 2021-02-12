#pragma once
#include <iostream>

//en.cppreference.com

namespace SiriusFM{
	class DiffusionCIR{
		private:
			double const m_cappa;
			double const m_sigma;
			double const m_theta;
			double const m_s0;
		public:
			double mu(doubles a_s, double t) const{
				return m_cappa * (m_theta - a_s);
			}

			double sigma(doubles a_s, double t) const{
				if(a_s < 0) return 0.0; //return((a_s < 0) ? 0 : m_sigma * a_s);
				return m_sigma * std::sqrt(a_s);
			}
			DiffusionCIR(double a_cappa, double a_sigma, double a_theta, double a_s0)
			: m_cappa(a_cappa),
			  m_sigma(a_sigma),
			  m_theta(a_theta),
			  m_s0(a_s0){
				if(m_sigma <= 0) throw std::invalid_argument("...");
				if(m_cappa < 0)  throw std::invalid_argument("...");
				if(m_theta <= 0) throw std::invalid_argument("...");
			}
			double GetStartPoint() const{
				return m_s0;
			}
	};
}
