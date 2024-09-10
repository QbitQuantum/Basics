int CompressFile(char* infile, char* outfile)
{
    return spawnl(P_WAIT, "huf", "huf", infile, outfile, NULL) & 255;
}