#ifndef _OregonDecoderV2_h
#ifdef __cplusplus
#define _OregonDecoderV2_h

#include "DecodeOOK.h"

class OregonDecoderV2 : public DecodeOOK {
protected:
    virtual char decode (word width);
public:
    OregonDecoderV2();
    void gotBit (char value);
};

#endif
#endif
