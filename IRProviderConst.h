#pragma once
#include "IRProvider.h"
#include "Time.h"
#include <cmath>

namespace SiriusFM{
    template <>
    class IRProvider <IRModeE::Const>{
        private:
            double m_IRs[int(CcyE::N)];
        public:
            IRProvider(char const * a_file);

            // Instantaneous continuously-compounded interest rate:
            double r(CcyE a_ccy, double a_t)const{
                return m_IRs[int(a_ccy)];
            }

            // Discount Factor:
           double DF(CcyE a_ccy, time_t a_t0, time_t a_t1) const{
             double y = YearFracInt(a_t1 - a_t0);
             return exp(- m_IRs[int(a_ccy)] * y);
           }
    };
    //-------------------------------------------------------------------------//
    // Alias:                                                                  //
    //-------------------------------------------------------------------------//
    using IRPConst = IRProvider<IRModeE::Const>;
}
