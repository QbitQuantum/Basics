int main(void)
{
    int counter;
    int maxval=-1;
    datastruct* svalues[200];
    for(counter=0;counter<200;counter++)
    {
        svalues[counter]=getinput();
        if(!svalues[counter]) break;
        maxval=counter;
    }
    printmessage(svalues[maxval/2]);
    return 0;
}