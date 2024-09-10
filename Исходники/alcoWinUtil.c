/*++

TclNewOctalObj

    Creates a new object from an octal value.

Arguments:
    octal   - The octal value to use.

Return Value:
    A pointer to a newly created object.

--*/
Tcl_Obj *
TclNewOctalObj(
    unsigned long octal
    )
{
    char value[12];
    StringCchPrintfA(value, ARRAYSIZE(value), "%03lo", octal);
    return Tcl_NewStringObj(value, -1);
}