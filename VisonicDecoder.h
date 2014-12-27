#ifndef _VisonicDecoder_h
#ifdef __cplusplus
#define _VisonicDecoder_h

#include "DecodeOOK.h"

// 868 MHz decoders

class VisonicDecoder : public DecodeOOK {
    public:
        VisonicDecoder ();
    
    virtual char decode (word width);
};

#endif
#endif
