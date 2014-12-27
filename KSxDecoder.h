#ifndef _KSxDecoder_h
#ifdef __cplusplus
#define _KSxDecoder_h

#include "DecodeOOK.h"

// 868 MHz decoders

class KSxDecoder : public DecodeOOK {
public:
    KSxDecoder ();
    
    // see also http://www.dc3yc.homepage.t-online.de/protocol.htm
    virtual char decode (word width);
};

#endif
#endif
