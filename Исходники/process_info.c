// Return None to represent NoSuchProcess, else return NULL for
// other exception or the name as a Python string
PyObject*
psutil_get_name(long pid)
{
    HANDLE h = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 pe = { 0 };
    pe.dwSize = sizeof(PROCESSENTRY32);

    if( Process32First(h, &pe)) {
        do {
            if (pe.th32ProcessID == pid) {
                CloseHandle(h);
                return Py_BuildValue("s", pe.szExeFile);
            }
        } while(Process32Next(h, &pe));

        // the process was never found, set NoSuchProcess exception
        NoSuchProcess();
        CloseHandle(h);
        return NULL;
    }

    CloseHandle(h);
    return PyErr_SetFromWindowsErr(0);
}