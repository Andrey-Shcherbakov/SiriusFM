#include "IRProviderConst.h"
#include <cstdio>
#include <cstdlib>

#define BUF_SIZE 1024
#define CCY_SIZE 3

namespace SiriusFM{
    IRProvider<IRModeE::Const>::IRProvider(char const * a_file){
        for(int k = 0; k < int(CcyE::N); ++k)
			m_IRs[k] = 0; //setting all rates to zero
        if(a_file == nullptr || *a_file == '\0') return;
        FILE *fp;
        char buff[BUF_SIZE];
        fp = fopen(a_file, "r"); // reading interest rates from file
        while(fgets(buff, BUF_SIZE, (FILE*)fp) != nullptr){
            buff[CCY_SIZE] = '\0';
            int code = int(Str2Ccy(buff));
            double R = std::atof(buff + CCY_SIZE + 1);
            m_IRs[code] = R;
        }
        fclose(fp);
    }
}
