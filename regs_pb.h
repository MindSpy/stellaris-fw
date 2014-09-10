/* Automatically generated nanopb header */
/* Generated by nanopb-0.3.0 at Wed Sep 10 15:45:37 2014. */

#ifndef PB_REGS_PB_H_INCLUDED
#define PB_REGS_PB_H_INCLUDED
#include <pb.h>

#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Enum definitions */
typedef enum _Request_Action {
    Request_Action_ECHO = 0,
    Request_Action_GET_STATE = 2,
    Request_Action_SET_STATE = 3,
    Request_Action_SAMPLES = 1,
    Request_Action_TEST = 4,
    Request_Action_LED = 5,
    Request_Action_STIMULATE = 6
} Request_Action;

typedef enum _Response_ErrNo {
    Response_ErrNo_NO_ERROR = 0,
    Response_ErrNo_HANDLER_MISSING = 1,
    Response_ErrNo_HANDLER_FAILED = 2
} Response_ErrNo;

/* Struct definitions */
typedef PB_BYTES_ARRAY_T(32) Request_payload_t;

typedef struct _Request {
    Request_Action action;
    uint64_t timestamp;
    bool has_start;
    uint32_t start;
    bool has_count;
    uint32_t count;
    bool has_payload;
    Request_payload_t payload;
    bool has_stream;
    bool stream;
    uint32_t reqid;
    bool has_module;
    int32_t module;
} Request;

typedef struct _Sample {
    uint64_t sequence;
    pb_size_t payload_count;
    int32_t payload[32];
} Sample;

typedef struct _State {
    uint32_t address;
    uint32_t payload;
} State;

typedef struct _Response {
    bool has_error;
    Response_ErrNo error;
    bool has_error_msg;
    char error_msg[32];
    uint64_t timestamp;
    pb_callback_t state;
    pb_callback_t sample;
    uint32_t reqid;
    bool has_module;
    int32_t module;
} Response;

/* Default values for struct fields */
extern const bool Request_stream_default;
extern const int32_t Request_module_default;
extern const Response_ErrNo Response_error_default;
extern const int32_t Response_module_default;

/* Initializer values for message structs */
#define Request_init_default                     {(Request_Action)0, 0, false, 0, false, 0, false, {0, {0}}, false, false, 0, false, -1}
#define State_init_default                       {0, 0}
#define Sample_init_default                      {0, 0, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}
#define Response_init_default                    {false, Response_ErrNo_NO_ERROR, false, "", 0, {{NULL}, NULL}, {{NULL}, NULL}, 0, false, -1}
#define Request_init_zero                        {(Request_Action)0, 0, false, 0, false, 0, false, {0, {0}}, false, 0, 0, false, 0}
#define State_init_zero                          {0, 0}
#define Sample_init_zero                         {0, 0, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}
#define Response_init_zero                       {false, (Response_ErrNo)0, false, "", 0, {{NULL}, NULL}, {{NULL}, NULL}, 0, false, 0}

/* Field tags (for use in manual encoding/decoding) */
#define Request_action_tag                       1
#define Request_timestamp_tag                    2
#define Request_start_tag                        3
#define Request_count_tag                        4
#define Request_payload_tag                      5
#define Request_stream_tag                       6
#define Request_reqid_tag                        7
#define Request_module_tag                       8
#define Sample_sequence_tag                      1
#define Sample_payload_tag                       2
#define State_address_tag                        1
#define State_payload_tag                        2
#define Response_error_tag                       1
#define Response_error_msg_tag                   2
#define Response_timestamp_tag                   3
#define Response_state_tag                       4
#define Response_sample_tag                      5
#define Response_reqid_tag                       6
#define Response_module_tag                      7

/* Struct field encoding specification for nanopb */
extern const pb_field_t Request_fields[9];
extern const pb_field_t State_fields[3];
extern const pb_field_t Sample_fields[3];
extern const pb_field_t Response_fields[8];

/* Maximum encoded size of messages (where known) */
#define Request_size                             82
#define State_size                               12
#define Sample_size                              363

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
