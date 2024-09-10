void arp_table::get_arp_table()
{
    //функция, возвращающая arp-таблицу
    //table - указатель на arp-таблицу
    //size - размер
    //true - таблица отсортированна в порядке возрастания ip адресов
    GetIpNetTable(table, &size, true);
    table = (PMIB_IPNETTABLE) new MIB_IPNETTABLE[size];
    //продолжить работу, если функция отработала без ошибок
    if (GetIpNetTable(table, &size, true) != NO_ERROR)
        return;
    _table = new Cell[table->dwNumEntries - 4];
    _count = 0;
    for (int i = 0; i < table->dwNumEntries - 4; i++)
    {
        mac_to_string(table->table[i].bPhysAddr, table->table[i].dwPhysAddrLen, mac);
        switch (table->table[i].dwType)
        {
            case 1:
                strcpy(type, "other");
                break;
            case 2:
                strcpy(type, "Invalidated");
                break;
            case 3:
                strcpy(type, "Dynamic");
                break;
            case 4:
                strcpy(type, "Static");
                break;
            default:
                strcpy(type,"");
        }
        //структура, представляет собой ip адрес (в различных типах данных)
        struct in_addr adr;
        adr.s_addr = table->table[i].dwAddr;
        item = new Cell();
        strcpy(item->ip, inet_ntoa(adr));
        strcpy(item->mac, mac);
        strcpy(item->type, type);
        if (strcmp(item->mac,"")!=0)
        {
            *(_table + _count) = *item;
            _count++;
        }
        delete item;
    }
}