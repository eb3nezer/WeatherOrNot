#ifndef _CrestaDecoder_h
#ifdef __cplusplus
#define _CrestaDecoder_h

#include "DecodeOOK.h"
#include <Arduino.h>

class CrestaDecoder : public DecodeOOK {
    public:
        CrestaDecoder ();
    
        virtual char decode (word width);
};

#endif
#endif
