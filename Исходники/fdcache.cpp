int Cryption::encrypt(int fd){
  AutoSeededRandomPool prng;
  string encryptedBytes, encodedKey, decodedKey;

  encodedKey = getKey();
  cout<<"Encode: "<<encodedKey<<endl;
  StringSource(encodedKey, true, new HexDecoder(new StringSink(decodedKey)));
  cout<<"Decode: "<<decodedKey<<endl;
  const byte* ebyteKey = (const byte*) decodedKey.data();

  string encodedIV;
  //createIV
  byte IVBytes[AES::BLOCKSIZE];
  prng.GenerateBlock(IVBytes, sizeof(IVBytes));
  StringSource(IVBytes, sizeof(IVBytes), true, new HexEncoder(new StringSink(encodedIV)));

  encryptedBytes = read(fd);

  string encryptedContents;
  //Encrypting the file contents
  try{
    CBC_Mode< AES >::Encryption e;
    e.SetKeyWithIV(ebyteKey, CryptoPP::AES::DEFAULT_KEYLENGTH, IVBytes);
    StringSource file(encryptedBytes, true, new StreamTransformationFilter(e,new StringSink(encryptedContents)));
  }
  catch( const CryptoPP::Exception& e ){
    cerr << e.what() << endl;
    exit(1);
  }

  string output = encodedIV + encryptedContents;
  const char *bufContents = output.c_str();
  ssize_t WriteLength = pwrite(fd, bufContents, output.length(), 0);
  ftruncate(fd, output.length());
  
  return 0;
}