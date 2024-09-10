        void OutboundMessageFragments::sendDataCallback(PeerState ps, uint32_t const msgId)
        {
            std::lock_guard<std::mutex> lock(m_mutex);

            auto itr = m_states.find(msgId);
            if(itr != m_states.end()) {
                OutboundMessageState& oms = itr->second;

                std::vector<PacketBuilder::FragmentPtr> fragList;
                auto fragment = oms.getNextFragment();

                if (fragment == nullptr) {
                    throw std::runtime_error("no ssu fragment when sending");
                }

                fragList.push_back(fragment);

                oms.markFragmentSent(fragList[0]->fragNum);

                PacketPtr p = PacketBuilder::buildData(ps.getEndpoint(), false, CompleteAckList(), PartialAckList(), fragList);
                p->encrypt(ps.getCurrentSessionKey(), ps.getCurrentMacKey());
                m_context.sendPacket(p);

                if(!oms.allFragmentsSent())
                    m_context.ios.post(boost::bind(&OutboundMessageFragments::sendDataCallback, this, ps, msgId));
            }
        }