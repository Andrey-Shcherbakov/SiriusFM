#pragma once
#include <iostream>
#include "Option.h"

namespace siriusFM{
	class EurCallOption final : public Option{ //the last "child class" in the hierarchy
		private:
			double const m_K; //K > 0
		public:
			EurCallOption(double a_K, int a_Tdays)
			: Option(a_Tdays, false),
              m_K(a_K){
                //Checks:
                if(m_K <= 0) throw std::invalid_argument("m_K <= 0");
			};
            ~EurCallOption() override{};
            double payoff (long a_L, double const * a_t, double const * a_s)
            const override{ //declaration and initialixation of abstact function from parent class
                assert(a_L > 0 && a_s != nullptr);
                return std::max<double>(a_s[a_L -1] - m_K, 0.0);
            };
	};

    class EurPutOption final : public Option{ //the last "child class" in the hierarchy
		private:
			double const m_K; //K > 0
		public:
			EurPutOption(double a_K, int a_Tdays)
			: Option(a_Tdays, false),
              m_K(a_K){
                //Checks:
                if(m_K <= 0) throw std::invalid_argument("m_K <= 0");
			};
            ~EurPutOption() override{};

            double payoff (long a_L, double const * a_t, double const * a_s)
            const override{ //declaration and initialixation of abstact function from parent class
                assert(a_L > 0 && a_s != nullptr);
                return std::max<double>(m_K - a_s[a_L -1], 0.0);
            };
	};
}
