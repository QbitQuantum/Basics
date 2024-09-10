char
ToAsciiUS(char code)
{
        char ascii;
        ascii=tecladoUS[shift][code];
        if( caps && !shift && IsLetter(ascii) )
            ascii=ToUpper(ascii);
        else if( caps && shift && IsLetter(ascii) )
            ascii=ToLower(ascii);
        return ascii;
}