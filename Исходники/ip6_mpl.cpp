void Mpl::HandleRetransmissionTimer(void)
{
    uint32_t now = TimerMilli::GetNow();
    uint32_t nextDelta = 0xffffffff;
    MplBufferedMessageMetadata messageMetadata;

    Message *message = mBufferedMessageSet.GetHead();
    Message *nextMessage = NULL;

    while (message != NULL)
    {
        nextMessage = message->GetNext();
        messageMetadata.ReadFrom(*message);

        if (messageMetadata.IsLater(now))
        {
            // Calculate the next retransmission time and choose the lowest.
            if (messageMetadata.GetTransmissionTime() - now < nextDelta)
            {
                nextDelta = messageMetadata.GetTransmissionTime() - now;
            }
        }
        else
        {
            // Update the number of transmission timer expirations.
            messageMetadata.SetTransmissionCount(messageMetadata.GetTransmissionCount() + 1);

            if (messageMetadata.GetTransmissionCount() < GetTimerExpirations())
            {
                Message *messageCopy = message->Clone(message->GetLength() - sizeof(MplBufferedMessageMetadata));

                if (messageCopy != NULL)
                {
                    if (messageMetadata.GetTransmissionCount() > 1)
                    {
                        messageCopy->SetSubType(Message::kSubTypeMplRetransmission);
                    }

                    GetIp6().EnqueueDatagram(*messageCopy);
                }

                messageMetadata.GenerateNextTransmissionTime(now, kDataMessageInterval);
                messageMetadata.UpdateIn(*message);

                // Check if retransmission time is lower than the current lowest one.
                if (messageMetadata.GetTransmissionTime() - now < nextDelta)
                {
                    nextDelta = messageMetadata.GetTransmissionTime() - now;
                }
            }
            else
            {
                mBufferedMessageSet.Dequeue(*message);

                if (messageMetadata.GetTransmissionCount() == GetTimerExpirations())
                {
                    if (messageMetadata.GetTransmissionCount() > 1)
                    {
                        message->SetSubType(Message::kSubTypeMplRetransmission);
                    }

                    // Remove the extra metadata from the MPL Data Message.
                    messageMetadata.RemoveFrom(*message);
                    GetIp6().EnqueueDatagram(*message);
                }
                else
                {
                    // Stop retransmitting if the number of timer expirations is already exceeded.
                    message->Free();
                }
            }
        }

        message = nextMessage;
    }

    if (nextDelta != 0xffffffff)
    {
        mRetransmissionTimer.Start(nextDelta);
    }
}