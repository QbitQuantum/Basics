int main(int argc, char* argv[])
{
  string encoded_mac;
  string line;
  ifstream encrypted_file(argv[1]);
  int count=0;
  string str_cipher, str_fkey, cipher;
  //encrypted_file.read(encoded_mac,64-1);
  if(encrypted_file.is_open())
    getline(encrypted_file,encoded_mac);
  while(!encrypted_file.eof()){
    getline(encrypted_file,str_cipher);
  }
  encrypted_file.close();


  StringSource(argv[2], true, new HexDecoder(
                                             new StringSink(str_fkey)
                                             )
               );

  byte fkey[str_fkey.length()];
  for (int i=0;i<=str_fkey.length();i++)
    fkey[i]=(byte)str_fkey[i];

  byte iv[AES::BLOCKSIZE]; // 16 bytes
  iv[0] = 0;

  string encoded, recovered;
  StringSource(str_cipher, true, new HexDecoder(
                                                new StringSink(cipher))
               );

  SecByteBlock mac_key(16);
  for (int i=0;i<sizeof(mac_key);i++){
    mac_key[i]=1;
  }
  string mac;

  // This step performs AES decryption

  try
    {
      CTR_Mode< AES >::Decryption d;
      d.SetKeyWithIV(fkey, sizeof(fkey), iv);

      // The StreamTransformationFilter removes
      //  padding as required.

      StringSource s(cipher, true,
                     new StreamTransformationFilter(d,
                                                    new StringSink(recovered)
                                                    )
                     ); // StringSource

      cout << "recovered text: " << recovered << endl;
    }
  catch(const CryptoPP::Exception& e)
    {
      cerr << e.what() << endl;
      exit(1);
    }


  StringSource(encoded_mac, true,
               new HexDecoder(
                              new StringSink(mac)
                              ) // HexEncoder
               );

  try
    {
      HMAC< SHA256 > hmac(mac_key, mac_key.size());
      const int flags = HashVerificationFilter::THROW_EXCEPTION | HashVerificationFilter::HASH_AT_END;
      StringSource(recovered + mac, true,
                   new HashVerificationFilter(hmac, NULL, flags)
                   ); // StringSource
      cout<<endl<<endl;
      cout << "HMAC has been implemented and plaintext message is verified" << endl;
    }
  catch(const CryptoPP::Exception& e)
    {
      cerr << e.what() << endl;
      exit(1);
    }

  return 0;
}