bool ioget_int_8bit (IO& io, int* result)
{
    int c = io.getc();
    if (c == io.EOS) {
        e_printf ("Unexpected EOS");
        return false;
    }

    *result = c;
    return true;
}