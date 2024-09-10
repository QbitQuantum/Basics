      virtual void Shuffle()
      {
        Random &rand = Random::GetInstance();
        if((rand.GetInt(0, 1024) / 1024.0) > N) {
          ShuffleRound::Shuffle();
          return;
        }

        SetTriggered();

        for(int idx = 0; idx < _server_state->shuffle_input.count(); idx++) {
          for(int jdx = 0; jdx < _server_state->shuffle_input.count(); jdx++) {
            if(idx == jdx) {
              continue;
            }
            if(_server_state->shuffle_input[idx] != _server_state->shuffle_input[jdx]) {
              continue;
            }
            qWarning() << "Found duplicate cipher texts... blaming";
            _state->blame = true;
          }
        }

        int x = Random::GetInstance().GetInt(0, _server_state->shuffle_input.count());
        int y = Random::GetInstance().GetInt(0, _server_state->shuffle_input.count());
        while(y == x) {
          y = Random::GetInstance().GetInt(0, _server_state->shuffle_input.count());
        }

        _server_state->shuffle_input[x] = _server_state->shuffle_input[y];
  
        QVector<int> bad;
        QSharedPointer<OnionEncryptor> oe;
        if(Utils::MultiThreading) {
          oe = QSharedPointer<OnionEncryptor>(new ThreadedOnionEncryptor());
        } else {
          oe = QSharedPointer<OnionEncryptor>(new OnionEncryptor());
        }

        if(!oe->Decrypt(_server_state->outer_key, _server_state->shuffle_input,
              _server_state->shuffle_output, &bad))
        {
          qWarning() << GetGroup().GetIndex(GetLocalId()) << GetLocalId() <<
            ": failed to decrypt layer due to block at indexes" << bad;
          _state->blame = true;
        } 
        
        oe->RandomizeBlocks(_server_state->shuffle_output);
        
        const Id &next = GetShufflers().Next(GetLocalId());
        MessageType mtype = (next == Id::Zero()) ? ENCRYPTED_DATA : SHUFFLE_DATA;
        
        QByteArray msg;
        QDataStream out_stream(&msg, QIODevice::WriteOnly);
        out_stream << mtype << GetRoundId() << _server_state->shuffle_output;
          
        if(mtype == ENCRYPTED_DATA) {
          VerifiableBroadcast(msg);
        } else {
          VerifiableSend(next, msg);
        }

        _state_machine.StateComplete();
      }