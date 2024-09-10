void misc() 
{
    char *bufp;
    int size=0;

/* $begin execve */
Execve("a.out", NULL, NULL);
/* $end execve */


/* $begin mmap */
bufp = Mmap(-1, size, PROT_READ, MAP_PRIVATE|MAP_ANON, 0, 0);
/* $end mmap */
}