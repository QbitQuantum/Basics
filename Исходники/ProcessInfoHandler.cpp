    void ProcessInfoHandler::OnDeleteRequest(const Safir::Dob::EntityRequestProxy entityRequestProxy,
                                             Safir::Dob::ResponseSenderPtr    responseSender)
    {
        if (m_connection.IsCreated(entityRequestProxy.GetEntityId()))
        {
            ProcessInfoPtr procInfo = boost::static_pointer_cast<ProcessInfo>
                (m_connection.Read(entityRequestProxy.GetEntityId()).GetEntity());

            for (auto name = procInfo->ConnectionNames().begin(); name != procInfo->ConnectionNames().end(); ++name)
            {
                const ConnectionId id(Connections::Instance().NodeId(),
                    -1,  // dummy context (context is part of the connection name)
                    (Connection::CalculateIdentifier
                    (Typesystem::Utilities::ToUtf8(*name))));
                ConnectionPtr connection = Connections::Instance().GetConnection(id);

                connection->SendStopOrder();
            }
        }

        responseSender->Send(Safir::Dob::SuccessResponse::Create());
    }