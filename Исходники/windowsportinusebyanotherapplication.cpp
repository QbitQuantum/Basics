PMIB_TCPTABLE_OWNER_MODULE WindowsPortInUseByAnotherApplication::getTCPTables()
{
    PVOID tcpTable = NULL;
    DWORD size = 0;
    DWORD result = 0;
    // Primer de tot, hem de trobar el tamany de la taula TCP i guardar-lo a size, un cop el tenim, podem fer el malloc i tornar
    // a cridar la funció per recuperar de forma correcta la taula.
    // El problema ve perqué la funció no retorna el tamany de forma acurada (sempre retorna un valor diferent), 
    // per tant, podem buscar-lo amb un while i quan es compleixi la variable pTCPTable estarà instanciada de forma correcta.
    bool found = false;
    while (!found)
    {
        // Buscar el tamany
        GetExtendedTcpTable(NULL, &size, true, AF_INET, TCP_TABLE_OWNER_MODULE_ALL, 0);
        // Es reserva l'espai per la taula TCP ara que sabem el tamany
        tcpTable = malloc(size);
        // S'obté la taula TCP
        result = GetExtendedTcpTable(tcpTable, &size, true, AF_INET, TCP_TABLE_OWNER_MODULE_ALL, 0);
        // Si ens dona error de tamany, ho tornem a probar
        if (result == ERROR_INSUFFICIENT_BUFFER)
        {
            free(tcpTable);
        }
        else if (result == NO_ERROR)
        {
            // Si no dona cap error ja podem plegar
            found = true;
        }
        else
        {
            // Si ens dona un error diferent, el loguem i retornem null
            found = true;
            ERROR_LOG(QString("Error al obtenir la taula TCP: %1").arg(GetLastError()));
            free(tcpTable);
            tcpTable = NULL;
        }
    }

    return (PMIB_TCPTABLE_OWNER_MODULE)tcpTable;
}