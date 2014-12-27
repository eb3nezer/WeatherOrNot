#ifndef _KakuDecoder_h
#ifdef __cplusplus
#define _KakuDecoder_h

#include "DecodeOOK.h"

class KakuDecoder : public DecodeOOK {
    public:
        KakuDecoder ();
    
        virtual char decode (word width);
};

#endif
#endif
