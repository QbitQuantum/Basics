void MySkype::OnConversationListChange(const ConversationRef &conversation, const Conversation::LIST_TYPE &type, const bool &added){

  if (type == Conversation::LIVE_CONVERSATIONS)
  {
    Conversation::LOCAL_LIVESTATUS liveStatus;
    if (!conversation->GetPropLocalLivestatus(liveStatus)) throw SkypeException("Can't obtain contact status.\n");
    SEString liveStatusAsString = tostring(liveStatus);
    printf("[SKYPE]: OnConversationListChange : %s\n", (const char*)liveStatusAsString);

    if (liveStatus == Conversation::RINGING_FOR_ME || liveStatus == Conversation::NONE)
    {
        printf("[SKYPE]: RING RING..\n");
        printf("[SKYPE]: Picking up call from MySkype::OnConversationListChange\n");
        // Saving the currently live conversation reference..
        liveSession = conversation->ref();
        liveSession.fetch();

  // -----------------------------------------------

        if (!liveSession->GetParticipants(liveSession->callerList, Conversation::OTHER_CONSUMERS)) throw SkypeException("Can't obtain participants.\n");
        SEString peopleCalling[liveSession->callerList.size()];

        for (uint i = 0; i < liveSession->callerList.size(); i++)
        {
            //Añadir conversaciones a la tabla. Luego cuando se quiera aceptar uno, obtener la conversacion por ID y hacerle un JoinLiveSession
            peopleCalling[i] = (const char*)liveSession->callerList[i]->GetProp(Participant::P_IDENTITY);

            wxString aux(std::string(peopleCalling[i]).c_str(), wxConvUTF8);

            std::string s_aux = (liveStatus == Conversation::RINGING_FOR_ME)?"Calling":"Call finished";
            wxString aux2(s_aux.c_str(), wxConvUTF8);

            time_t mytime = time(0);
            wxString aux3(std::string(asctime(localtime(&mytime))).c_str(), wxConvUTF8);
            /*
            incoming_calls->ClearAll();
            long itemIndex = incoming_calls->InsertItem(0, aux);

            incoming_calls->SetItem(itemIndex, 1, aux2);
            incoming_calls->SetItem(itemIndex, 2, aux3);

            */

            //TODO: NINONI
            std::string auxiliar;
            auxiliar = "";
            auxiliar.append(std::string(peopleCalling[i]).c_str());
            auxiliar.append(" - ");
            auxiliar.append(s_aux.c_str());
            auxiliar.append(" - ");
            auxiliar.append(std::string(asctime(localtime(&mytime))).c_str());

            incomingCall_event = true;
            incomingCall_message = auxiliar;//std::string(peopleCalling[i]).c_str();


        };

        if (!liveSession->GetParticipants(liveSession->callerList, Conversation::ALL)) throw SkypeException("Can't obtain participants.\n");
        fetch(liveSession->callerList);
  // -----------------------------------------------
    };
  };
};