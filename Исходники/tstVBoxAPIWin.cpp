int listVMs(IVirtualBox *virtualBox)
{
    HRESULT rc;

    SAFEARRAY *machinesArray = NULL;

    rc = virtualBox->get_Machines(&machinesArray);
    if (SUCCEEDED(rc))
    {
        IMachine **machines;
        rc = SafeArrayAccessData(machinesArray, (void **) &machines);
        if (SUCCEEDED(rc))
        {
            for (ULONG i = 0; i < machinesArray->rgsabound[0].cElements; ++i)
            {
                CComBSTR str;
                rc = machines[i]->get_Name(&str);
                if (SUCCEEDED(rc))
                {
                    printf("Name: %S\n", str);
                }
            }

            SafeArrayUnaccessData(machinesArray);
        }

        SafeArrayDestroy(machinesArray);
    }

    return 0;
}