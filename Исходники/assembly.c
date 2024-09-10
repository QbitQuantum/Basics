static HRESULT parse_pe_header(ASSEMBLY *assembly)
{
    IMAGE_DATA_DIRECTORY *datadirs;

    assembly->nthdr = ImageNtHeader(assembly->data);
    if (!assembly->nthdr)
        return E_FAIL;

    if (assembly->nthdr->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC)
    {
        IMAGE_OPTIONAL_HEADER64 *opthdr =
                (IMAGE_OPTIONAL_HEADER64 *)&assembly->nthdr->OptionalHeader;
        datadirs = opthdr->DataDirectory;
    }
    else
    {
        IMAGE_OPTIONAL_HEADER32 *opthdr =
                (IMAGE_OPTIONAL_HEADER32 *)&assembly->nthdr->OptionalHeader;
        datadirs = opthdr->DataDirectory;
    }

    if (!datadirs)
        return E_FAIL;

    if (!datadirs[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR].VirtualAddress ||
        !datadirs[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR].Size)
    {
        return E_FAIL;
    }

    assembly->corhdr = ImageRvaToVa(assembly->nthdr, assembly->data,
        datadirs[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR].VirtualAddress, NULL);
    if (!assembly->corhdr)
        return E_FAIL;

    return S_OK;
}