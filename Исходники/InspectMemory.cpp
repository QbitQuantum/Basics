void InspectMemory::OnInspectbut()
{
    // TODO: Add your control notification handler code here

    char address_str[9];
    m_edit1.GetWindowText(address_str, 9);
    if (address_str[0]==0) return;

    char size_str[9];
    m_edit_2.GetWindowText(size_str, 9);
    if (size_str[0]==0) return;

    unsigned int caddress = GenericPurposeMethods::ConvertHexStringToInt(address_str);

    int size = GenericPurposeMethods::StringToNumber(size_str);

    HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
                                   FALSE, processid);

    if (hProcess==NULL)
        return;


    unsigned long dwTotalRead;

    char* valuestr = new char[1];
    valuestr[0] = 00;

    unsigned char* valbytes = new unsigned char[size];
    int isok = ReadProcessMemory(hProcess, (LPVOID)caddress, valbytes,
                                 size, &dwTotalRead);

    if (isok != 0)  // if read didn't failed
    {
        valuestr = GenericPurposeMethods::BytesToString(valbytes, size, CString(_T("bytes")).GetBuffer(0), CString(_T("hexadecimal")).GetBuffer(0));
    }
    else
    {
        valuestr = _T("Read failed!!!");
    }


    m_result_edit.SetWindowText(valuestr);


}