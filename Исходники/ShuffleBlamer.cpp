  void ShuffleBlamer::CheckShuffle()
  {
    for(int gidx = 0; gidx < _group.Count(); gidx++) {
      if(_rounds[gidx]->GetState() == ShuffleRound::BLAME_SHARE) {
        continue;
      }

      Set(gidx, "Wrong state");
    }

    // If any failures ... let's not try to deal with the logic at this point...
    if(_set) {
      return;
    }

    _inner_data = _rounds[_group.GetIndex(_shufflers.GetId(0))]->GetShuffleCipherText();

    QSharedPointer<Crypto::OnionEncryptor> oe;
    if(Utils::MultiThreading) {
      oe = QSharedPointer<Crypto::OnionEncryptor>(new Crypto::ThreadedOnionEncryptor());
    } else {
      oe = QSharedPointer<Crypto::OnionEncryptor>(new Crypto::OnionEncryptor());
    }

    for(int idx = 0; idx < _private_keys.count(); idx++) {
      QVector<QByteArray> outdata;
      QVector<int> bad;
      oe->Decrypt(_private_keys[idx], _inner_data, outdata, &bad);
      _inner_data = outdata;
      if(bad.count() == 0) {
        continue;
      }
      foreach(int bidx, bad) {
        Set(bidx, "Invalid crypto data");
      }
    }