#ifndef _OregonDecoderV3_h
#ifdef __cplusplus
#define _OregonDecoderV3_h

#include "DecodeOOK.h"

class OregonDecoderV3 : public DecodeOOK {
	public:
        OregonDecoderV3();

        virtual void gotBit (char value);
        virtual char decode (word width);
};

#endif
#endif 
