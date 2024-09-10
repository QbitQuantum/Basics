int main(int argc, char** argv)
{
   if( argc != 2)
   {
       printf("usage: getprotobynumber prot\n");
       return 1;
   }
   struct protoent prot;
   memcpy(&prot, getprotobynumber((int)atoi(argv[1])), sizeof(prot));
   printf("name:%s\n prot: %d\n", prot.p_name, prot.p_proto);
}