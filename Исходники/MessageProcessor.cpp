bool MessageProcessor::processMessage(const std::string& messageString,
                                      std::string& reply)
{
    if (messageString.size() < 1) return false;

    // First we grab the client's message
    OTASCIIArmor ascMessage;
    ascMessage.MemSet(messageString.data(), messageString.size());

    String messageContents;
    ascMessage.GetString(messageContents);
    // All decrypted--now let's load the results into an OTMessage.
    // No need to call message.ParseRawFile() after, since
    // LoadContractFromString handles it.
    Message message;
    if (!messageContents.Exists() ||
        !message.LoadContractFromString(messageContents)) {
        Log::vError("Error loading message from message "
                    "contents:\n\n%s\n\n",
                    messageContents.Get());
        return true;
    }

    Message replyMessage;
    replyMessage.m_strCommand.Format("%sResponse", message.m_strCommand.Get());
    // NymID
    replyMessage.m_strNymID = message.m_strNymID;
    // NotaryID, a hash of the server contract
    replyMessage.m_strNotaryID = message.m_strNotaryID;
    // The default reply. In fact this is probably superfluous
    replyMessage.m_bSuccess = false;

    ClientConnection client;
    Nym nym(message.m_strNymID);

    bool processedUserCmd = server_->userCommandProcessor_.ProcessUserCommand(
        message, replyMessage, &client, &nym);

    // By optionally passing in &client, the client Nym's public
    // key will be set on it whenever verification is complete. (So
    // for the reply, I'll  have the key and thus I'll be able to
    // encrypt reply to the recipient.)
    if (!processedUserCmd) {
        String s1(message);

        Log::vOutput(0, "Unable to process user command: %s\n ********** "
                        "REQUEST:\n\n%s\n\n",
                     message.m_strCommand.Get(), s1.Get());

        // NOTE: normally you would even HAVE a true or false if
        // we're in this block. ProcessUserCommand()
        // is what tries to process a command and then sets false
        // if/when it fails. Until that point, you
        // wouldn't get any server reply.  I'm now changing this
        // slightly, so you still get a reply (defaulted
        // to success==false.) That way if a client needs to re-sync
        // his request number, he will get the false
        // and therefore know to resync the # as his next move, vs
        // being stuck with no server reply (and thus
        // stuck with a bad socket.)
        // We sign the reply here, but not in the else block, since
        // it's already signed in cases where
        // ProcessUserCommand() is a success, by the time that call
        // returns.

        // Since the process call definitely failed, I'm
        replyMessage.m_bSuccess = false;
        // making sure this here is definitely set to
        // false (even though it probably was already.)
        replyMessage.SignContract(server_->GetServerNym());
        replyMessage.SaveContract();

        String s2(replyMessage);

        Log::vOutput(0, " ********** RESPONSE:\n\n%s\n\n", s2.Get());
    }
    else {
        // At this point the reply is ready to go, and client
        // has the public key of the recipient...
        Log::vOutput(1, "Successfully processed user command: %s.\n",
                     message.m_strCommand.Get());
    }

    String replyString(replyMessage);

    if (!replyString.Exists()) {
        Log::vOutput(0, "Failed trying to grab the reply "
                        "in OTString form. "
                        "(No reply message will be sent.)\n");
        return true;
    }

    OTASCIIArmor ascReply(replyString);

    if (!ascReply.Exists()) {
        Log::vOutput(0, "Unable to WriteArmoredString from "
                        "OTASCIIArmor object into OTString object. (No reply "
                        "message will be sent.)\n");
        return true;
    }

    reply.assign(ascReply.Get(), ascReply.GetLength());

    return false;
}