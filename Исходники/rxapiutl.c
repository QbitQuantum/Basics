// UnsignedToRxResult -- Convert a numeric code to Result.
//
//      Return: return of 'StringToRxResult'
//
ULONG UnsignedToRxResult(
    ULONG number,                       // Code to convert.
    PRXSTRING rxResult)                 // REXX function result.
{
    UCHAR string[34];
    ULONG cc;

    _ultoa(number, string, 10);

    cc = StringToRxResult(string, strlen(string), rxResult);
    return cc;
}