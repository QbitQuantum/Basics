int main(int argc, char* argv[])
{
  if (argc != 7){
    printf("Hashchecker needs to know the cryptographic details of your wallet!\nUsage: hashchecker pw_to_permute iterations salt crypted_key public_key crypted_secret\n");
    return 1;
  }
  CCrypter crypter;
  CKeyingMaterial vMasterKey;

  // Try any password as input
  SecureString attempt = argv[1];

  const unsigned int nDeriveIterations = atoi(argv[2]);//29731;
  const vector<unsigned char> chSalt = Convert(argv[3]);//"b29a2e128e8e0a2f");//argv[1];
  const vector<unsigned char> vchCryptedKey = Convert(argv[4]);//"982a07407ccb8d70514e7b7ccae4b53d68318ec41fd2bf99bf9dbcafd2f150a92c6eb8f9ea743b782fc5b85403421c1d");//argv[2];
  const vector<unsigned char> vchPubKey = Convert(argv[5]);//"03fefd771544971f3ab95b041bbce02cc799a335d0d12c3bcd46c7c61a4e3ba897");
  const vector<unsigned char> vchCryptedSecret = Convert(argv[6]);//"17169083a74b07ff3497027af7423b9aec1593c90f15a57f52c368593947c85e37b03430840ad48ef409e97ba5a4cdeb");

  double count = Factorial(attempt.size());
  bool found = false;

  for (int i = 0; i <= count; i++)
    {
      if (i > 0) {//test the word as typed in on first iteration
        permutation(i-1, attempt);
      }

      const SecureString strWalletPassphrase = attempt;
      cout << i << "-" << strWalletPassphrase <<"\n";
      if(!crypter.SetKeyFromPassphrase(strWalletPassphrase, chSalt, nDeriveIterations, 0))
        {
          cout << i << " " << strWalletPassphrase <<"\n";
          continue;
        }
      if (!crypter.Decrypt(vchCryptedKey, vMasterKey))
        {
          cout << i << " " << strWalletPassphrase <<"\n";
          continue;
        }

      CSecret vchSecret;
      if(!DecryptSecret(vMasterKey, vchCryptedSecret, Hash(vchPubKey.begin(), vchPubKey.end()), vchSecret))
        {
          cout << "** didn't decrypt **" <<"\n";
          continue;
        }
      if (vchSecret.size() != 32)
        {
          cout << "** wrong size secret **" <<"\n";
          continue;
        }
      CKey key;
      key.SetPubKey(vchPubKey);
      key.SetSecret(vchSecret);
      if (key.GetPubKey() == vchPubKey)
        {
          cout<<"Found one: "<<strWalletPassphrase<<"\n";
          found = true;
          break;
        }
      // else
      //     cout << "** didn't get the pubkey back **\n";
    }
  if (found)
    cout << "Found it! Congratulations\n";
  return 0;
}