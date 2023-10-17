/******************************************************************************
 * @file message.c
 * @brief Encode/Decoder functions for nanopb message
 * @author Lojik
 * @version 1.0.0
 ******************************************************************************/

#include <zephyr/kernel.h>
#include <pb_encode.h>
#include <pb_decode.h>

#include "message.h"

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(nanopb, CONFIG_MODULE_LOG_LEVEL);

bool encode_message(uint8_t *buffer, size_t buffer_size, size_t *message_length)
{
    bool status;

    Msg message = Msg_init_zero;

    /* Create a stream that will write to our buffer. */
    pb_ostream_t stream = pb_ostream_from_buffer(buffer, buffer_size);

    /* Fill in the message here */

    /* Now we are ready to encode the message! */
    status = pb_encode(&stream, Msg_fields, &message);
    *message_length = stream.bytes_written;

    if (!status)
    {
        LOG_ERR("Encoding failed: %s", PB_GET_ERROR(&stream));
    }

    return status;
}

bool decode_message(uint8_t *buffer, size_t message_length)
{
    bool status;

    Msg message = Msg_init_zero;

    /* Create a stream that reads from the buffer. */
    pb_istream_t stream = pb_istream_from_buffer(buffer, message_length);

    /* Now we are ready to decode the message. */
    status = pb_decode(&stream, Msg_fields, &message);

    /* Check for errors... */
    if (status)
    {
        /* Print the data contained in the message. */
    }
    else
    {
        LOG_ERR("Decoding failed: %s\n", PB_GET_ERROR(&stream));
    }

    return status;
}