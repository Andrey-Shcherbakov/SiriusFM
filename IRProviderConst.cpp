#include "IRProviderConst.h"
#include <cstdio>
#include <cstdlib>

namespace siriusFM{
    IRProvider<IRModeE::Const>::IRProvider(char const * a_file){
        memset(m_IRS, 0.0, int(CcyE::N)); //setting all rates to zero
        FILE *fp;
        char buff[255];
        fp = fopen(a_file, "r"); // reading interest rates from file
        while(fgets(buff, 255, (FILE*)fp) != nullptr){
            buff[3] = '\0';
            int code = int(Str2Ccy(buff));
            double R = std::atof(buff + 4);
            m_IRS[code] = R;
        }
        fclose(fp);
    }
}

int main() {
    return 0;
}
