#include "KSxDecoder.h"

    KSxDecoder::KSxDecoder () {}
    
    // see also http://www.dc3yc.homepage.t-online.de/protocol.htm
    char KSxDecoder::decode (word width) {
        if (200 <= width && width < 1000) {
            byte w = width >= 600;
            switch (state) {
                case UNKNOWN:
                    gotBit(w);
                    bits = pos = 0;
                    if (data[0] != 0x95)
                        state = UNKNOWN;
                    break;
                case OK:
                    state = w == 0 ? T0 : T1;
                    break;
                case T0:
                    gotBit(1);
                    if (!w)
                        return -1;
                    break;
                case T1:
                    gotBit(0);
                    if (w)
                        return -1;
                    break;
            }
        } else if (width >= 1500 && pos >= 6)
            return 1;
        else
            return -1;
        return 0;
    }
