int main(int argc, char*argv[]){
       BigInt  cipher, deciphered,message;
        unsigned long int *a;
        unsigned long int arr[10];
        a=&arr[0];
        BigInt pubkey, privatekey;
        BigInt gnm;
		
		//message=1000;
       message = int(((double)(std::rand())/RAND_MAX)*RAND_LIMIT32);
        
        for(int i=1;i<=10;i++)
     {
      sleep(1);
      std::cout<<std::endl<<"RSA "<<i<<std::endl;     
      RSA newrsa;    // default , no args, program generates its own p and q
      std::cout<<"Public Key ";
      pubkey= newrsa.getPublicKey();
      pubkey.toULong(a,4);
       std::cout<<*a<<std::endl;
       privatekey=newrsa.getPrivateKey();
       privatekey.toULong(a,4);
       std::cout<<"Private Key : "<<*a<<std::endl;
       gnm = newrsa.getModulus();
       std::cout<<"N  is "<<gnm.toHexString()<<std::endl;
        
       cipher = newrsa.encrypt(message);
       deciphered = newrsa.decrypt(cipher);

       std::cout<<"message: "<<message.toHexString()<<"\tcipher: "<<cipher.toHexString()<<"\tdeciphered: "<<deciphered.toHexString()<<std::endl<<std::endl;     
     }
     
     
}