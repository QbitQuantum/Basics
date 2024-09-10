void GenerateKeyPair(std::string& public_key, std::string & private_key)
{
    std::string strprivkey, strpubkey;    
    AutoSeededRandomPool rng;
    InvertibleRSAFunction privkey;
    
    privkey.Initialize(rng, 1024);
    
    Base64Encoder privkeysink(new StringSink(strprivkey), false);
    privkey.DEREncode(privkeysink);
    privkeysink.MessageEnd();
        
    RSAFunction pubkey(privkey);
    
    Base64Encoder pubkeysink(new StringSink(strpubkey), false);
    pubkey.DEREncode(pubkeysink);
    pubkeysink.MessageEnd();
    
    public_key = strpubkey;
    
    private_key = strprivkey;	
}