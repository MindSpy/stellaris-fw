#ifndef MEMORYSTREAM_H
#define MEMORYSTREAM_H

#include "ProtocolWrapper.h"

class MemoryStream : public Stream
{
public:
    MemoryStream(char*, char*, const size_t);
    ~MemoryStream();
    int available();
    size_t readBytes( char *, size_t );
    size_t write(const uint8_t *, size_t );
private:
    char* in;
    char* out;
    size_t len;
    size_t iptr;
    size_t optr;
};

#endif // MEMORYSTREAM_H