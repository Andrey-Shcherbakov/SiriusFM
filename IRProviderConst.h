#pragma once
#include "IRProvider.h"

namespace siriusFM{
    template <>
    class IRProvider <IRModeE::Const>{
        private:
            double m_IRS[int(CcyE::N)];
        public:
            IRProvider(char const * a_file);
            double r(CcyE a_ccy, double a_t)const{
                return m_IRS[int(a_ccy)];
            };
    };
}
