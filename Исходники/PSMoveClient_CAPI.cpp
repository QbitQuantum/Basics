PSMResult PSM_PollNextMessage(PSMMessage *message, size_t message_size)
{
    PSMResult result= PSMResult_Error;

    // Poll events queued up by the call to ClientPSMoveAPI::update()
    ClientPSMoveAPI::Message message_internal;
    if (ClientPSMoveAPI::poll_next_message(&message_internal, sizeof(message_internal)))
    {
        assert(sizeof(PSMMessage) == message_size);
        assert(message != nullptr);

        switch (message_internal.payload_type)
        {
        case ClientPSMoveAPI::_messagePayloadType_Response:
            {
                message->payload_type= PSMMessage::_messagePayloadType_Response;
                extractResponseMessage(&message_internal.response_data, &message->response_data);
            } break;
        case ClientPSMoveAPI::_messagePayloadType_Event:
            {
                // Update event flags before handling off the event
                processEvent(&message_internal.event_data);

                // Package up the event
                message->payload_type= PSMMessage::_messagePayloadType_Event;
                message->event_data.event_type= static_cast<PSMEventMessage::eEventType>(message_internal.event_data.event_type);
                message->event_data.event_data_handle= static_cast<PSMEventDataHandle>(message_internal.event_data.event_data_handle);

            } break;
        default:
            assert(0 && "unreachable");
        }

        result= PSMResult_Success;
    }

    return result;
}