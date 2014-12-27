#ifndef _XrfDecoderV2_h
#ifdef __cplusplus
#define _XrfDecoderV2_h

#include "DecodeOOK.h"

class XrfDecoder : public DecodeOOK {
public:
    XrfDecoder ();
    
    // see also http://davehouston.net/rf.htm
    virtual char decode (word width);
};

#endif
#endif
