void main(void)
{
    int i;

#ifdef DYNAMIC    /* If we use dynamic array, allocate RAM for it    */
    Data = (struct Record *)calloc(9,sizeof(struct Record));
    if (Data == NULL)
    {
        fputs("ERROR! couldn't allocate enough RAM!\n",stderr);
        exit(1);
    }
#endif

    /* Handy shorthand for initializing the array */
#define INITIALIZE(y,z) strcpy(Data[i].Name,y);Data[i].Ext=z; i++

    /*** Set up the data in the array ***/
    i=0;
    INITIALIZE("Marco C. Mason",    566);
    INITIALIZE("Mark W. Crane",        531);
    INITIALIZE("Jody Gilbert",        507);
    INITIALIZE("Duane Spurlock",    528);
    INITIALIZE("Tara Billinger",    539);
    INITIALIZE("Tim Landgrave",        556);
    INITIALIZE("Douglas Cobb",        523);
    INITIALIZE("Maureen Pawley",    508);
    INITIALIZE("Karl Feige",        559);

    /*** Sort the list by telephone extension ***/
    qsort(Data, 9, sizeof(struct Record),RecordCompare);

    /*** Print the resulting phone list ***/
#ifdef DYNAMIC
    puts("Phone list output (using DYNAMIC array)");
#else
    puts("Phone list output (using STATIC array)");
#endif

    puts("\nRecord  Telephone\nNumber  Extension  Name");
    for (i=0; i<9; i++)
        printf("  %02d       %03d     %s\n",
               i+1,    Data[i].Ext,   Data[i].Name);
}