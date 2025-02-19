#ifndef STREAM_H
#define STREAM_H

#include "utility.h"

class StreamCipher : public CipherBase {
public:
    using CipherBase::CipherBase; //inherit constructor
    void process() override; //process implementaitno
};

#endif