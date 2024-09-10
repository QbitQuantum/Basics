ThreadError Client::SendCopy(const Message &aMessage, const Ip6::MessageInfo &aMessageInfo)
{
    ThreadError error;
    Message *messageCopy = NULL;

    // Create a message copy for lower layers.
    VerifyOrExit((messageCopy = aMessage.Clone(aMessage.GetLength() - sizeof(RequestMetadata))) != NULL,
                 error = kThreadError_NoBufs);

    // Send the copy.
    SuccessOrExit(error = mSocket.SendTo(*messageCopy, aMessageInfo));

exit:

    if (error != kThreadError_None && messageCopy != NULL)
    {
        messageCopy->Free();
    }

    return error;
}