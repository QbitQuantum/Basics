int main(int argc, char* argv[]){

if(argc!=2){
printf("%s","Usage: <executable name> <password> \n");
exit(1);
}

createtable();

extract(); //extracts secret data (in binary) to secret[]

decrypt(argv[1]); //decompresses and decrypts the received stego object

decompress();

printf("Secret message written to message.txt\n");

return 0;
}