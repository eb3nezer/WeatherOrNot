#include "FSxDecoder.h"

    FSxDecoder::FSxDecoder () {}
    
    // see also http://fhz4linux.info/tiki-index.php?page=FS20%20Protocol
    char FSxDecoder::decode (word width) {
        if (300 <= width && width < 775) {
            byte w = width >= 500;
            switch (state) {
                case UNKNOWN:
                    if (w == 0)
                        ++flip;
                    else if (flip > 20)
                        state = T1;
                    else
                        return -1;
                    break;
                case OK:
                    state = w == 0 ? T0 : T1;
                    break;
                case T0:
                    gotBit(0);
                    if (w)
                        return -1;
                    break;
                case T1:
                    gotBit(1);
                    if (!w)
                        return -1;
                    break;
            }
        } else if (width >= 1500 && pos >= 5)
            return 1;
        else
            return -1;
        return 0;
    }

