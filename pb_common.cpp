#include <pb_encode.h>
#include <pb_decode.h>
#include "pb_common.h"

#define _PB_DEBUG

#ifdef _PB_DEBUG
#include <Logging.h>
#endif

// TODO: this is in question - does it work?
#ifndef SIZE_MAX
#define SIZE_MAX ~((size_t)0)
#endif

#define C_ARRAY_LENGTH(_name) sizeof(_name)/sizeof(*_name)

Stream*  StreamWrapper::_serial;
response_handler_t* StreamWrapper::_handlers;
uint8_t StreamWrapper::_handler_count;

void StreamWrapper::init(Stream* serial, response_handler_t* handlers, uint8_t handler_count) {
  _serial = serial;
  _handlers = handlers;
  _handler_count = handler_count;
}

void StreamWrapper::handle(void) {
  Request request;
  Response response;
  
  pb_istream_t istream = {&StreamWrapper::read_callback, StreamWrapper::_serial, SIZE_MAX};
  pb_ostream_t ostream = {&StreamWrapper::write_callback, StreamWrapper::_serial, SIZE_MAX, 0};
  
  // intercept request message
  if (!pb_decode_delimited(&istream, Request_fields, &request)) {
#ifdef _PB_DEBUG
    Log.error("Message decoding failed."CR, response.error_msg);
#endif
    return;
  }
  
#ifdef _PB_DEBUG
  Log.debug("<- {reqid=%i, action=%d}"CR, request.reqid, request.action);
#endif
  
  //defaults
  response.has_error = false;
  response.has_error_msg = false;
  response.has_module = false;
  response.timestamp = micros();
  response.sample.funcs.encode = NULL;
  response.state.funcs.encode = NULL;
  response.reqid = request.reqid;
  
  // determine handler based on request
  response_handler_t* handler = NULL;
  for (int i = 0; i < _handler_count; i++) {
    if (_handlers[i].action == request.action) {
      handler = &_handlers[i];
      break;
    }
  }
  if (handler == NULL) {
    response.has_error = true;
    response.error = Response_ErrNo_HANDLER_MISSING;
    response.has_error_msg = true;
    sprintf(response.error_msg, "Missing handler for action #%d.", request.action);
#ifdef _PB_DEBUG
    Log.debug("%s"CR, response.error_msg);
#endif
    // serialize response message
    if (!pb_encode_delimited(&ostream, Response_fields, &response)) {
#ifdef _PB_DEBUG
    Log.error("Serialization of response message failed."CR);
#endif
      return;
    }
  } else {
    do {
      response.timestamp = micros();
      if (!(*handler->handler)(&request, &response)) {
        if (!response.has_error){
          response.has_error = true;
          response.error = Response_ErrNo_HANDLER_FAILED;
          if (!response.has_error_msg) {
            response.has_error_msg = true;
            sprintf(response.error_msg, "No error message provided.");
          }
        }
#ifdef _PB_DEBUG
        Log.debug("%s"CR, response.error_msg);
#endif
      }
      // serialize response message
      if (!pb_encode_delimited(&ostream, Response_fields, &response)) {
#ifdef _PB_DEBUG
    Log.error("Serialization of response message failed."CR);
#endif
        return;
      }
      
#ifdef _PB_DEBUG
  Log.debug("-> {reqid=%d}"CR, response.reqid);
#endif
      
    } while (request.stream && (!_serial->available()));  
  } 
}

bool StreamWrapper::write_callback(pb_ostream_t *stream, const uint8_t *buf, size_t count) {
    return _serial->write(buf, count) == count;
}

bool StreamWrapper::read_callback(pb_istream_t *stream, uint8_t *buf, size_t count) {
  size_t avail = 0;
  while (avail < count) {
    avail = _serial->available();
    delayMicroseconds(1);
  }
  size_t result = _serial->readBytes((char*)buf, constrain(avail,0,count));
  return result == count;
}

