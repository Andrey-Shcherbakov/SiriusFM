#pragma once
#include <iostream>
#include <cstring>

namespace SiriusFM{
    enum class CcyE{ //currencies
        UNDEFINED = -1,
        USD = 0,
        EUR = 1,
        GBP = 2,
        CHF = 3,
        JPY = 4,
        RUB = 5,
        N   = 6
    };

    enum class IRModeE{ //provider mode
        Const = 0,
        Fwdcurve = 1,
        Stock = 2
    };

    inline char const * Ccy2Str(CcyE a_ccy){ //converting map num to str
        switch(a_ccy){
            case CcyE::USD: return "USD";
            case CcyE::EUR: return "EUR";
            case CcyE::GBP: return "GBP";
            case CcyE::CHF: return "CHF";
            case CcyE::JPY: return "JPY";
            case CcyE::RUB: return "RUB";
            default: throw std::invalid_argument("...");
        }
    };

    inline CcyE Str2Ccy (char const * a_str){ //converting str to map number
        if(strcmp(a_str, "USD") == 0) return CcyE::USD;
        else if(strcmp(a_str, "EUR") == 0) return CcyE::EUR;
        else if(strcmp(a_str, "GBP") == 0) return CcyE::GBP;
        else if(strcmp(a_str, "CHF") == 0) return CcyE::CHF;
        else if(strcmp(a_str, "JPY") == 0) return CcyE::JPY;
        else if(strcmp(a_str, "RUB") == 0) return CcyE::RUB;
        else throw std::invalid_argument("...");
    };

    template <IRModeE IRM> //Provider class declaration
    class IRProvider;
}
