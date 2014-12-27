#include "EMxDecoder.h"

    // 868 MHz decoders
    
    EMxDecoder::EMxDecoder () {}
    
    // see also http://fhz4linux.info/tiki-index.php?page=EM+Protocol
    char EMxDecoder::decode (word width) {
        if (200 <= width && width < 1000) {
            byte w = width >= 600;
            switch (state) {
                case UNKNOWN:
                    if (w == 0)
                        ++flip;
                    else if (flip > 20)
                        state = OK;
                    else
                        return -1;
                    break;
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
        } else if (width >= 1500 && pos >= 9)
            return 1;
        else
            return -1;
        return 0;
    }

