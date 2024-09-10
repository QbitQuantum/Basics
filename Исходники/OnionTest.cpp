  void SoMuchEvil(OnionEncryptor &oe)
  {
    int count = Random::GetInstance().GetInt(10, 20);
    int changed0 = Random::GetInstance().GetInt(0, count - 5);
    int changed1 = Random::GetInstance().GetInt(changed0 + 1, count + 1);
    int mchanged0 = Random::GetInstance().GetInt(0, count);
    int mchanged1 = Random::GetInstance().GetInt(0, count);

    Library *lib = CryptoFactory::GetInstance().GetLibrary();

    QVector<QSharedPointer<AsymmetricKey> > private_keys;
    QVector<QSharedPointer<AsymmetricKey> > public_keys;
    for(int idx = 0; idx < count; idx++) {
      private_keys.append(QSharedPointer<AsymmetricKey>(lib->CreatePrivateKey()));
      public_keys.append(QSharedPointer<AsymmetricKey>(private_keys.last()->GetPublicKey()));
    }

    QVector<QByteArray> cleartexts;
    QVector<QByteArray> ciphertexts;
    QScopedPointer<Random> rand(lib->GetRandomNumberGenerator());

    for(int idx = 0; idx < count; idx++) {
      QByteArray cleartext(1500, 0);
      rand->GenerateBlock(cleartext);
      QByteArray ciphertext;
      EXPECT_EQ(oe.Encrypt(public_keys, cleartext, ciphertext, 0), -1);
      cleartexts.append(cleartext);
      ciphertexts.append(ciphertext);
    }

    QVector<QVector<QByteArray> > onions(count + 1);
    onions.last() = ciphertexts;

    // Find first evil peer

    for(int idx = count - 1; idx >= changed1; idx--) {
      EXPECT_TRUE(oe.Decrypt(private_keys[idx], onions[idx + 1], onions[idx], 0));
      oe.RandomizeBlocks(onions[idx]);
    }

    QVector<QSharedPointer<AsymmetricKey> > swap_keys(public_keys);
    swap_keys.resize(changed1);

    QByteArray cleartext(1500, 0);
    rand->GenerateBlock(cleartext);
    EXPECT_EQ(oe.Encrypt(swap_keys, cleartext, onions[changed1][mchanged1], 0), -1);

    // Find second evil peer

    for(int idx = changed1 - 1; idx >= changed0; idx--) {
      EXPECT_TRUE(oe.Decrypt(private_keys[idx], onions[idx + 1], onions[idx], 0));
      oe.RandomizeBlocks(onions[idx]);
    }

    swap_keys.resize(changed0);

    rand->GenerateBlock(cleartext);
    EXPECT_EQ(oe.Encrypt(swap_keys, cleartext, onions[changed0][mchanged0], 0), -1);

    for(int idx = changed0 - 1; idx >= 0; idx--) {
      EXPECT_TRUE(oe.Decrypt(private_keys[idx], onions[idx + 1], onions[idx], 0));
      oe.RandomizeBlocks(onions[idx]);
    }

    QBitArray bad;
    EXPECT_FALSE(oe.VerifyAll(private_keys, onions, bad));

    int good_count = 0;
    int bad_count = 0;
    for(int idx = 0; idx < count; idx++) {
      if(idx == changed0 || idx == changed1) {
        EXPECT_TRUE(bad[idx]);
      } else {
        EXPECT_FALSE(bad[idx]);
      }
      onions.first().contains(cleartexts[idx]) ? good_count++ : bad_count++;
    }
    EXPECT_TRUE(good_count >= count - 2);
    EXPECT_TRUE(good_count < count);
    EXPECT_TRUE(bad_count > 0);
    EXPECT_TRUE(bad_count <= 2);
  }