int main(void)
{
    char buf[0x80]; /* storage for keeping the SPrintf result string */
    ULONG args[2];  /* storage for keeping the SPrintf arguments */

    args[0] = (ULONG) "result";
    args[1] = (ULONG) "PUTCHARPROTO macro";

    SPrintf("I am the %s of using SPrintf() with the new %s!", buf, args);

    printf("%s\n", buf); /* just a simple printf to output and add the \n */

return( 0);
}