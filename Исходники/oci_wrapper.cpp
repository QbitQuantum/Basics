int OWStatement::GetInteger( OCINumber* ppoData )
{
    sb4 nRetVal;

    CheckError( OCINumberToInt(
        hError,
        ppoData,
        (uword) sizeof(sb4),
        OCI_NUMBER_SIGNED,
        (dvoid *) &nRetVal ),
        hError );

    return nRetVal;
}