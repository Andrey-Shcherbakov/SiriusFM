#pragma once
#include <iostream>

namespace siriusFM{
    class Option{
        protected: //can be seen from our class hierarchy
            bool const m_IsAmerican;
            int  const m_Tdays; //Tdays > 0

            Option(int a_Tdays, bool a_IsAmerican)
            :m_IsAmerican(a_IsAmerican),
             m_Tdays(a_Tdays){
                //Checks:
                if(m_Tdays <= 0)  throw std::invalid_argument("m_Tdays <= 0");
            };
        public:
            bool IsAmerican() const{
                return m_IsAmerican;
            };

            virtual double payoff (long a_L, double const * a_t, double const * a_s) const = 0; // vertual smth = 0 means that this method is abstract

            virtual ~Option(){};
    };
}
