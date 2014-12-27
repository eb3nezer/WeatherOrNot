#ifndef _EMxDecoderV2_h
#ifdef __cplusplus
#define _EMxDecoderV2_h

#include "DecodeOOK.h"

// 868 MHz decoders

class EMxDecoder : public DecodeOOK {
public:
    EMxDecoder ();
    
    // see also http://fhz4linux.info/tiki-index.php?page=EM+Protocol
    virtual char decode (word width);
};

#endif
#endif
