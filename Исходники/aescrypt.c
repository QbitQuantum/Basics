/*
 *  cleanup
 *
 *  Removes output files that are not fully and properly created.
 */
void cleanup(const wchar_t *outfile)
{
    if (wcscmp(outfile,L"-") && outfile[0] != '\0')
    {
        _wunlink(outfile);
    }
}