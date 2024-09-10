// Проверяет, можно ли считать таблицей нечто с адресом p и шириной элементов N
static bool slow_check_for_data_table (int N, byte *p, uint32 &type, BYTE *&table_start, BYTE *&table_end, byte *bufstart, byte *bufend, byte *buf, uint64 &offset, Buffer &ReorderingBuffer)
{
    // Сначала сканируем назад, начиная с p, в поисках начала таблицы
    int useless;
    table_start = search_for_table_boundary (-N, p,           bufstart, bufend, useless);
    // Затем сканируем вперёд, начиная с table_start, в поисках конца таблицы
    table_end   = search_for_table_boundary (N,  table_start, bufstart, bufend, useless);

    // +разрешить таблицы с широкими столбцами и небольшим числом строк (sqrt(N)*rows >= X)
    // +учитывать расстояние до предыдущей таблицы для оптимизации конечного уровня сжатия
    // улучшать оценку для столбцов с фиксированной разницей между элементами (типа 8,16,24,32...)
    // считать количество байтов, энтропия которых уменьшилась от вычитания [как минимум на два бита]

    // Теперь выясняем, достаточно ли хороша эта таблица для того, чтобы её стоило закодировать
    int rows   = (table_end-table_start)/N;
    int useful = rows - useless;  // количество полезных строк таблицы
    double skipBits = logb(mymax(table_start-bufstart,1));  // сколько бит придётся потратить на кодирование поля skip
    stat ((slow_checks++, verbose>1 && printf ("Slow check  %08x-%08x (%d*%d+%d)\n", int(table_start-buf+offset), int(table_end-buf+offset), N, useful, useless)));
    if (useful*sqrt((double)N) > 30+4*skipBits) {
        stat ((table_count++,  table_sumlen += N*rows, table_skipBits+=skipBits));
        stat (verbose>0 && printf("%08x-%08x %d*%d   ", int(table_start-buf+offset), int(table_end-buf+offset), N, rows));

        // Определить какие столбцы нужно вычесть, а какие являются иммутабельными.
        // Вычесть вычитаемое и собрать иммутабельные столбцы в начале таблицы (для удобства работы lz77)
        bool doDiff[MAX_ELEMENT_SIZE], immutable[MAX_ELEMENT_SIZE];
        analyze_table (N, table_start, rows, doDiff, immutable);
        diff_table    (N, table_start, rows, doDiff);
        reorder_table (N, table_start, rows, immutable, ReorderingBuffer);
        type = encode_type (N, doDiff, immutable);
        stat (verbose>0 && printf("\n"));
        return TRUE;
    }

    return FALSE;
}