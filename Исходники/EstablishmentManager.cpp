        void EstablishmentManager::processRequest(EstablishmentStatePtr const &state)
        {
            state->calculateDHSecret();

            PacketPtr p = PacketBuilder::buildSessionCreated(state);
            p->encrypt(state->getIV(), state->getSessionKey(), state->getMacKey());

            const ByteArray& dhSecret = state->getDHSecret();
            SessionKey newKey(toSessionKey(dhSecret)), newMacKey;

            state->setSessionKey(newKey);

            copy(dhSecret.begin() + 32, dhSecret.begin() + 32 + 32, newMacKey.begin());
            state->setMacKey(newMacKey);

            m_context.sendPacket(p);

            state->setState(EstablishmentState::State::CREATED_SENT);
            post(state);
        }