#include "KakuDecoder.h"

    KakuDecoder::KakuDecoder () {}
    
    char KakuDecoder::decode (word width) {
        if (180 <= width && width < 450 || 950 <= width && width < 1250) {
            byte w = width >= 700;
            switch (state) {
                case UNKNOWN:
                case OK:
                    if (w == 0)
                        state = T0;
                    else
                        return -1;
                    break;
                case T0:
                    if (w)
                        state = T1;
                    else
                        return -1;
                    break;
                case T1:
                    state += w + 1;
                    break;
                case T2:
                    if (w)
                        gotBit(0);
                    else
                        return -1;
                    break;
                case T3:
                    if (w == 0)
                        gotBit(1);
                    else
                        return -1;
                    break;
            }
        } else if (width >= 2500 && 8 * pos + bits == 12) {
            for (byte i = 0; i < 4; ++i)
                gotBit(0);
            alignTail(2);
            return 1;
        } else
            return -1;
        return 0;
    }

