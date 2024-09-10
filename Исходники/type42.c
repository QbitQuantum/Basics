static BOOL LoadTable(HDC hdc, OTTable *table)
{
    unsigned int i;

    if(table->MS_tag == MS_MAKE_TAG('g','d','i','r')) return TRUE;
    table->len = GetFontData(hdc, table->MS_tag, 0, NULL, 0);
    table->data = HeapAlloc(GetProcessHeap(), 0, (table->len + 3) & ~3 );
    memset(table->data + ((table->len - 1) & ~3), 0, sizeof(DWORD));
    GetFontData(hdc, table->MS_tag, 0, table->data, table->len);
    table->check = 0;
    for(i = 0; i < (table->len + 3) / 4; i++)
        table->check += FLIP_ORDER(*((DWORD*)(table->data) + i));
    return TRUE;
}