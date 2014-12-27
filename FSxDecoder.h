#ifndef _FSxDecoder_h
#ifdef __cplusplus
#define _FSxDecoder_h

#include "DecodeOOK.h"

// 868 MHz decoders

class FSxDecoder : public DecodeOOK {
    public:
        FSxDecoder ();
    
    // see also http://fhz4linux.info/tiki-index.php?page=FS20%20Protocol
    virtual char decode (word width);
};

#endif
#endif
