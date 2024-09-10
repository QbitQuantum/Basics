AnsiString CreateGuid(void) 
{ 
    System::TGUID g;

    OleCheck (CoCreateGuid (&g)); 
    return (Sysutils::GUIDToString (g)); 
} 