#include <IRProviderConst.h>
#include <cstdio>
#include <cstdlib>

namespace siriusFM{
    IRProvider<IRModeE::Const>::IRProvider(char const * a_file){
        memset(m_IRS, 0.0, CcyE::N); //setting all rates to zero

        fp = fopen(a_file, "r"); // reading interest rates from file
        while(fgets(buff, 255, (FILE*)fp) != nullptr){
            buff[3] = '\0';
            int code = int(Str2Ccy(buff))
            double r = std::atof(buff + 4);
            m_IRS[code] = r;
        }
        fclose(fp);
    }
}
