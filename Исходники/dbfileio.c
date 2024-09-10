ACPI_OBJECT_TYPE8
AcpiDbMatchArgument (
    NATIVE_CHAR             *UserArgument,
    ARGUMENT_INFO           *Arguments)
{
    UINT32                  i;


    if (!UserArgument || UserArgument[0] == 0)
    {
        return (ACPI_TYPE_NOT_FOUND);
    }

    for (i = 0; Arguments[i].Name; i++)
    {
        if (STRSTR (Arguments[i].Name, UserArgument) == Arguments[i].Name)
        {
            return ((ACPI_OBJECT_TYPE8) i);
        }
    }

    /* Argument not recognized */

    return (ACPI_TYPE_NOT_FOUND);
}