NATIVE_CHAR *
AcpiUtStrupr (
    NATIVE_CHAR             *SrcString)
{
    NATIVE_CHAR             *String;


    FUNCTION_ENTRY ();


    /* Walk entire string, uppercasing the letters */

    for (String = SrcString; *String; )
    {
        *String = (char) TOUPPER (*String);
        String++;
    }


    return (SrcString);
}