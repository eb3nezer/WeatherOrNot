#ifndef _HezDecoder_h
#ifdef __cplusplus
#define _HezDecoder_h

#include "DecodeOOK.h"

class HezDecoder : public DecodeOOK {
    public:
        HezDecoder ();
    
    // see also http://homeeasyhacking.wikia.com/wiki/Home_Easy_Hacking_Wiki
    virtual char decode (word width);
};

#endif
#endif
