unsigned int GenerateChecksumV8(unsigned int sym, unsigned int salt)
{
    unsigned int a=sym;
    for(int i=0; i<1000; i++)
        a=TransformBlock(a, salt, 0x80, 0x40);
    return a;
}