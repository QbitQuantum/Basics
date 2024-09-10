int main (int argc, char** argv)
{   
    
    char * curfilename;
    char toprint;
    FILE * fp;
    int i = 1;
    
    while(argv[i]!=NULL)
    {
        if (strcmp(argv[i], "--help") == 0)
        {
            printf("Usage: cat-lite [--help] [FILE]...\n");
            printf("With no FILE, or when FILE is -, read standard input.\n\n");
            printf("Examples:\n");
            printf("  cat-lite README   Print the file README to standard output.\n");
            printf("  cat-lite f - g    Print f's contents, then standard input,\n                    then g's contents.\n");
            printf("  cat-lite          Copy standard input to standard output.\n");
            return EXIT_SUCCESS;
        }
        i++;
    }
    
    if(argv[1]==NULL)
    {
        fp = stdin;
        while(1)
        {
            toprint = fgetc(fp);
            if(feof(fp) == 1) {
                break;
            }
            fputc(toprint, stdout); // or printf("%c", toprint);
        }
    }
    
    i = 1;
    while(argv[i]!=NULL)
    {
        curfilename = argv[i];
        if(strcmp(curfilename, "-") == 0)
        {
            fp = stdin;
        }
        else
        {
            fp = fopen(curfilename, "r");
        }
        //might have to read file, count \n's, then set the size of the array to that.
        //char * filelines[256];
        if(fp == NULL)
        {
            fprintf(stderr, "cat cannot open %s\n", curfilename);
            return EXIT_FAILURE;
        }
        while(1)
        {
            toprint = fgetc(fp);
            if(feof(fp) == 1) {
                break;
            }
            fputc(toprint, stdout); // or printf("%c", toprint);
        }
        if(strcmp(curfilename, "-") != 0)
        {
            fclose(fp);
        }
        i++;
    }

    
    //while( fscanf("%s\n", filelines) != EOF)
    //{
    
    //}
    
    
    /*[zpaurus@ecelinux12 PA04]$ echo ... | ./cat-lite testcases/file3 - testcases/file4
I would not like them here or there.
I would not like them anywhere.
I do not like green eggs and ham.
I do not like them, Sam-I-Am.

...
Say! I like green eggs and ham!
I do! I like them, Sam-I-Am!
And I would eat them in a boat.
And I would eat them with a goat...
And I will eat them, in the rain.
And in the dark. And on a train.
And in a car. And in a tree.
They are so good, so good, you see!
So I will eat them in a box.
And I will eat them with a fox.
And I will eat them in a house.
And I will eat them with a mouse.
And I will eat them here and there.
Say! I will eat them anywhere!
I do so like green eggs and ham!
Thank you! Thank you, Sam-I-Am.*/
    
    return EXIT_SUCCESS;
}