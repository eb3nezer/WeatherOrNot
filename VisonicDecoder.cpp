#include "VisonicDecoder.h"

// 868 MHz decoders

    VisonicDecoder::VisonicDecoder () {}
    
    char VisonicDecoder::decode (word width) {
        if (200 <= width && width < 1000) {
            byte w = width >= 600;
            switch (state) {
                case UNKNOWN:
                case OK:
                    state = w == 0 ? T0 : T1;
                    break;
                case T0:
                    gotBit(!w);
                    if (w)
                        return 0;
                    break;
                case T1:
                    gotBit(!w);
                    if (!w)
                        return 0;
                    break;
            }
            // sync error, flip all the preceding bits to resync
            for (byte i = 0; i <= pos; ++i)
                data[i] ^= 0xFF; 
        } else if (width >= 2500 && 8 * pos + bits >= 36 && state == OK) {
            for (byte i = 0; i < 4; ++i)
                gotBit(0);
            alignTail(5); // keep last 40 bits
            // only report valid packets
            byte b = data[0] ^ data[1] ^ data[2] ^ data[3] ^ data[4];
            if ((b & 0xF) == (b >> 4))
                return 1;
        } else
            return -1;
        return 0;
    }

