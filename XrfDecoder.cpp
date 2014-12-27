#include "XrfDecoder.h"

    XrfDecoder::XrfDecoder () {}
    
    // see also http://davehouston.net/rf.htm
    char XrfDecoder::decode (word width) {
        if (width > 2000 && pos >= 4)
            return 1;
        if (width > 5000)
            return -1;
        if (width > 4000 && state == UNKNOWN)
            state = OK;
        else if (350 <= width && width < 1800) {
            byte w = width >= 720;
            switch (state) {
                case OK:
                    if (w == 0)
                        state = T0;
                    else
                        return -1;
                    break;
                case T0:
                    gotBit(w);
                    break;
            }
        } else
            return -1;
        return 0;
    }

