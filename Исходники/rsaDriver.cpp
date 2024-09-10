int main(int argc, char*argv[]){      /*********************************************************
 * A Simple Driver
 * *******************************************************
 */
     unsigned long int *a;
     unsigned long int arr[4];
     a=&arr[0];

       RSA myRSA;
	BigInt message, cipher, deciphered;

       message = int(((double)std::rand()/RAND_MAX)*RAND_LIMIT32);
       message.toULong(a,4);
       cipher = myRSA.encrypt(message);
       deciphered = myRSA.decrypt(cipher);
       std::cout<<*a<<std::endl;
  //  std::cout<<"message "<<message.toString();
std::cout<<"message: "<<message.toHexString()<<"\tcipher: "<<cipher.toHexString()<<"\tdeciphered: "<<deciphered.toHexString()<<std::endl;

}