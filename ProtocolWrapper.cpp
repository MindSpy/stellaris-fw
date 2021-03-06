#include "ProtocolWrapper.hpp"

#include <pb_encode.h>
#include <pb_decode.h>

#ifndef _UNITTEST
#include <Arduino.h>
#else
#include "compat.hpp"
#endif

namespace mindspy {

Stream* ProtocolWrapper::stream = NULL;

ProtocolWrapper::ProtocolWrapper() {
    handler.setStopCallback(ProtocolWrapper::stopStream);
}

ProtocolWrapper::~ProtocolWrapper() {
}

bool ProtocolWrapper::handle() {
    // volatile streams for nanopb library.
    pb_istream_t istream = { &read_callback, NULL, SIZE_MAX };
    pb_ostream_t ostream = { &write_callback, NULL, SIZE_MAX, 0 };

    // Handle incomming request.
    return handler.handle(&istream, &ostream);
}

void ProtocolWrapper::setStream(Stream * s) {
    stream = s;
}
void ProtocolWrapper::setSensors(mindspy::sensor::Sensors* sensors) {
    handler.setSensors(sensors);
}

bool ProtocolWrapper::stopStream(void) {
    return !!stream->available();
}

bool ProtocolWrapper::write_callback(pb_ostream_t *, const uint8_t *buf, size_t count) {
    return stream->write(buf, count) == count;
}

bool ProtocolWrapper::read_callback(pb_istream_t *, uint8_t *buf, size_t count) {
    size_t avail = 0;

    // wait for enough data
    while (avail < count) {
        avail = stream->available();
        delayMicroseconds(1);
    }

    size_t result = stream->readBytes((char*) buf, avail > count ? count : avail);
    return result == count;
}

} // namespace
