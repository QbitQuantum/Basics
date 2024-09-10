void AppServer::addRegistration(const Jid& user,
                                const std::string& stanzaId,
                                const std::string& node,
                                const XData& payload)
{
    using Action = typename PendingReg::Action;

    std::string deviceId {payload.getField("device-id").singleValue()};
    std::string deviceName {payload.getField("device-name").singleValue()};
    std::string token {payload.getField("token").singleValue()};
    std::string appId {payload.getField("application-id").singleValue()};

    if(deviceId.empty())
    {
        deviceId = user.getResource();
    }

    bool payloadOk;
    Backend::Type backendType;

    if(node == "register-push-apns")
    {
        payloadOk = not (deviceId.empty() or token.empty());
        backendType = Backend::Type::Apns;   
    }

    else if(node == "register-push-gcm")
    {
        payloadOk = not (deviceId.empty() or token.empty());
        backendType = Backend::Type::Gcm;
    }

    else if(node == "register-push-mozilla")
    {
        payloadOk = not (deviceId.empty() or token.empty());
        backendType = Backend::Type::Mozilla;
    }

    else if(node == "register-push-ubuntu")
    {
        payloadOk = not (deviceId.empty() or token.empty() or appId.empty());
        backendType = Backend::Type::Ubuntu;
    }

    else if(node == "register-push-wns")
    {
        payloadOk = not (deviceId.empty() or token.empty());
        backendType = Backend::Type::Wns;
    }

    else
    {
        sendCommandError(user,
                         stanzaId,
                         node,
                         "execute",
                         "modify",
                         "bad-request",
                         "malformed-action");
        return;
    }

    if(not payloadOk)
    {
        sendCommandError(user,
                         stanzaId,
                         node,
                         "execute",
                         "modify",
                         "bad-request",
                         "bad-payload");
        return;
    }

    Backend::IdT backendId {Backend::makeBackendId(backendType, getJid())};
    
    if(mBackends.find(backendId) == mBackends.cend())
    {
        sendCommandError(user, stanzaId, node, "execute", "modify", "item-not-found");
        return;
    }

    std::string secret {makeRandomString(32)};
    
    Registration reg
    {
        user,
        deviceId,
        deviceName,
        token,
        appId,
        backendId,
        std::time(nullptr)
    };

    // DEBUG:
    std::cout << "DEBUG: adding registration:" << std::endl
              << "user: "******"deviceId: " << reg.getDeviceId() << std::endl
              << "deviceName: " << reg.getDeviceName() << std::endl
              << "token: " << reg.getToken() << std::endl
              << "appId: " << reg.getAppId() << std::endl
              << "backendId: " << reg.getBackendId() << std::endl
              << "timestmap: " << reg.getTimestamp() << std::endl;

    auto regPred =
    [&user, &deviceId](const std::pair<NodeIdT, Registration>& p)
    {
        return 
        p.second.getUser().bare() == user.bare() and
        p.second.getDeviceId() == deviceId;
    };

    {
        std::lock_guard<std::mutex> lk {mRegsMutex};

        auto regResult = std::find_if(mRegs.begin(), mRegs.end(), regPred);

        if(regResult != mRegs.end())
        {
            deletePubsubNode(makeRandomString(), regResult->first);
            mRegs.erase(regResult);
        }
    }

    auto pendingPred =
    [&user, &deviceId](const std::pair<StanzaIdT, PendingReg>& p)
    {
        return
        p.second.getRegistration().getUser().bare() == user.bare() and
        p.second.getRegistration().getDeviceId() == deviceId;
    };

    auto pendingResult =
    std::find_if(mPendingRegs.begin(), mPendingRegs.end(), pendingPred);

    if(pendingResult != mPendingRegs.end())
    {
        deletePubsubNode(makeRandomString(), pendingResult->first);
        mPendingRegs.erase(pendingResult); 
    }

    std::string newNode {makeRandomString()};
    std::string createNodeId {makeRandomString()};

    XData nodeConfig
    {
        "submit",
        {
            {"hidden", "FORM_TYPE", {"http://jabber.org/protocol/pubsub#node_config"}},
            {"", "pubsub#secret", {secret}}
        }
    };

    mPendingRegs.insert({newNode, PendingReg {secret, stanzaId, reg}});
    mPendingActions.insert({createNodeId, {Action::CreateNode, newNode}});

    createPubsubNode(createNodeId, newNode, nodeConfig);
}