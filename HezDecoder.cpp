#include "HezDecoder.h"

    HezDecoder::HezDecoder () {}
    
    // see also http://homeeasyhacking.wikia.com/wiki/Home_Easy_Hacking_Wiki
    char HezDecoder::decode (word width) {
        if (200 <= width && width < 1200) {
            byte w = width >= 600;
            gotBit(w);
        } else if (width >= 5000 && pos >= 5 /*&& 8 * pos + bits == 50*/) {
            for (byte i = 0; i < 6; ++i)
                gotBit(0);
            alignTail(7); // keep last 56 bits
            return 1;
        } else
            return -1;
        return 0;
    }
