void elapsedToStringFPS(double elapsed, char* str)
{
    double fps = 1 / elapsed;

    int numDigits = 8;
    int decimal, sign;
    
    char* fpsStr = _ecvt(fps, numDigits, &decimal, &sign);
    
    if (decimal > 0)
    {
        strncpy(str, fpsStr, decimal);
        strncpy(str+decimal, ".", 1);
        strncpy(str+decimal+1, fpsStr+decimal, 2);
        str[decimal+3] = '\0';
    }
}