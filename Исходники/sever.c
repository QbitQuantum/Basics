void get_random(char outstring[],int count)
{
    int i=0,base=126-32;
    //get printable ascii character between 32-126
    for(i=0;i<count-1;i++)
      outstring[i]=toascii((rand()%base)+32);
    outstring[i]='\0';

}