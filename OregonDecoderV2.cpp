// Oregon V2 decoder added - Dominique Pierre
// Oregon V3 decod
#include "OregonDecoderV2.h"

    OregonDecoderV2::OregonDecoderV2() {}
    
    // add one bit to the packet data buffer
    void OregonDecoderV2::gotBit (char value) {
        if(!(total_bits & 0x01))
        {
            data[pos] = (data[pos] >> 1) | (value ? 0x80 : 00);
        }
        total_bits++;
        pos = total_bits >> 4;
        if (pos >= sizeof data) {
            resetDecoder();
            return;
        }
        state = OK;
    }
    
    char OregonDecoderV2::decode (word width) {
        if (200 <= width && width < 1200) {
            byte w = width >= 700;
            switch (state) {
                case UNKNOWN:
                    if (w != 0) {
                        // Long pulse
                        ++flip;
                    } else if (32 <= flip) {
                        // Short pulse, start bit
                        flip = 0;
                        state = T0;
                    } else {
                      // Reset decoder
                        return -1;
                    }
                    break;
                case OK:
                    if (w == 0) {
                        // Short pulse
                        state = T0;
                    } else {
                        // Long pulse
                        manchester(1);
                    }
                    break;
                case T0:
                    if (w == 0) {
                      // Second short pulse
                        manchester(0);
                    } else {
                        // Reset decoder
                        return -1;
                    }
                    break;
            }
        } else {
            return -1;
        }
        return total_bits == 160 ? 1: 0;
    }


