bool RequestProcessor::SendSubscriptionEnvelopeResponse(socket_t &sock, EnvelopeSubscriptionResponseState &state)
{
    if (!state.finalized && !(state.current_size > state.max_size || state.messages.size() > state.max_envelopes))
        return true;

    if (state.messages.size() == 0)
        return true;

    Envelope response;
    protocol::response::SubscriptionStartV1 start;
    start.set_id(state.id);
    start.add_to_envelope(response);

    if (!zeromq::SendEnvelope(sock, state.identities, response, true, ZMQ_SNDMORE)) {
        return false;
    }

    vector<message_t *>::iterator i = state.messages.begin();
    for (; i != state.messages.end(); i++) {
        sock.send(**i, i != state.messages.end() ? ZMQ_SNDMORE : 0);
        delete *i;
        *i = NULL;
    }

    state.messages.clear();
    state.current_size = 0;

    return true;
}