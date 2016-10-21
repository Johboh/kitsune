/* Automatically generated nanopb header */
/* Generated by nanopb-0.3.1 at Wed Oct 19 14:20:19 2016. */

#ifndef PB_MESSEJI_PB_H_INCLUDED
#define PB_MESSEJI_PB_H_INCLUDED
#include <pb.h>

#include "audio_commands.pb.h"

#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Enum definitions */
typedef enum _Message_Type {
    Message_Type_PLAY_AUDIO = 0,
    Message_Type_STOP_AUDIO = 1,
    Message_Type_SET_VOLUME = 2,
    Message_Type_VOICE_CONTROL = 3
} Message_Type;

typedef enum _MessageStatus_State {
    MessageStatus_State_PENDING = 0,
    MessageStatus_State_SENT = 1,
    MessageStatus_State_RECEIVED = 2,
    MessageStatus_State_EXPIRED = 3
} MessageStatus_State;

/* Struct definitions */
typedef struct _BatchMessage {
    pb_callback_t message;
} BatchMessage;

typedef struct _ReceiveMessageRequest {
    pb_callback_t sense_id;
    pb_callback_t message_read_id;
} ReceiveMessageRequest;

typedef struct _Message {
    pb_callback_t sender_id;
    int64_t order;
    bool has_message_id;
    int64_t message_id;
    Message_Type type;
    bool has_play_audio;
    PlayAudio play_audio;
    bool has_stop_audio;
    StopAudio stop_audio;
    bool has_volume;
    Volume volume;
    bool has_voice_control;
    VoiceControl voice_control;
} Message;

typedef struct _MessageStatus {
    int64_t message_id;
    MessageStatus_State state;
} MessageStatus;

/* Default values for struct fields */

/* Initializer values for message structs */
#define ReceiveMessageRequest_init_default       {{{NULL}, NULL}, {{NULL}, NULL}}
#define Message_init_default                     {{{NULL}, NULL}, 0, false, 0, (Message_Type)0, false, PlayAudio_init_default, false, StopAudio_init_default, false, Volume_init_default, false, VoiceControl_init_default}
#define BatchMessage_init_default                {{{NULL}, NULL}}
#define MessageStatus_init_default               {0, (MessageStatus_State)0}
#define ReceiveMessageRequest_init_zero          {{{NULL}, NULL}, {{NULL}, NULL}}
#define Message_init_zero                        {{{NULL}, NULL}, 0, false, 0, (Message_Type)0, false, PlayAudio_init_zero, false, StopAudio_init_zero, false, Volume_init_zero, false, VoiceControl_init_zero}
#define BatchMessage_init_zero                   {{{NULL}, NULL}}
#define MessageStatus_init_zero                  {0, (MessageStatus_State)0}

/* Field tags (for use in manual encoding/decoding) */
#define BatchMessage_message_tag                 1
#define ReceiveMessageRequest_sense_id_tag       1
#define ReceiveMessageRequest_message_read_id_tag 2
#define Message_sender_id_tag                    1
#define Message_order_tag                        2
#define Message_message_id_tag                   3
#define Message_type_tag                         4
#define Message_play_audio_tag                   5
#define Message_stop_audio_tag                   6
#define Message_volume_tag                       7
#define Message_voice_control_tag                8
#define MessageStatus_message_id_tag             1
#define MessageStatus_state_tag                  2

/* Struct field encoding specification for nanopb */
extern const pb_field_t ReceiveMessageRequest_fields[3];
extern const pb_field_t Message_fields[9];
extern const pb_field_t BatchMessage_fields[2];
extern const pb_field_t MessageStatus_fields[3];

/* Maximum encoded size of messages (where known) */
#define MessageStatus_size                       17

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
