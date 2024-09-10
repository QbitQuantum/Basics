int main (int argc,char **argv)

{
CheckOpts(argc,argv);
MonInitialize();
GetNameInfo();
GetInterfaceInfo();
GetV6InterfaceInfo();  
StartServer(argc,argv);
return 0;
}