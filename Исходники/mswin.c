/* acx1_rect ****************************************************************/
ACX1_API unsigned int ACX1_CALL acx1_rect
(
    uint8_t const * const * data, // array of rows of utf8 text with special escapes
    uint16_t start_row,
    uint16_t start_col,
    uint16_t row_num,
    uint16_t col_num,
    acx1_attr_t * attrs
)
{
    CHAR_INFO buf[0x2000];
    CHAR_INFO * ci;
    SMALL_RECT wr;
    COORD bs, bc;
    uint_t i, j, o, crt_attr, buf_rows;
    int l, cw;
    uint16_t a;
    uint32_t cp;


    start_row--;
    start_col--;
    if (start_row >= screen_height || start_col >= screen_width) return 0;
    if (row_num > screen_height - start_row) row_num = screen_height - start_row;
    if (col_num > screen_width - start_col) col_num = screen_width - start_col;

    buf_rows = ACX1_ITEM_COUNT(buf) / col_num;
    bs.X = col_num;
    bc.X = 0;
    bc.Y = 0;
    for (; row_num; row_num -= buf_rows, start_row += buf_rows, data += buf_rows)
    {
        if (row_num < buf_rows) buf_rows = row_num;
        for (ci = &buf[0], i = 0; i < buf_rows; ++i)
        {
            crt_attr = 0;
            a = prepare_attr(attrs[crt_attr].bg, attrs[crt_attr].fg,
                             attrs[crt_attr].mode);

            for (j = o = 0; data[i][o] && j < col_num; o += l, j += cw, ci += cw)
            {
                if (data[i][o] >= 0x80)
                {
                    l = acx1_utf8_char_decode_strict(data[i] + o, SSIZE_MAX, &cp);
                    if (l < 0) return ACX1_BAD_DATA;
                    cw = acx1_term_char_width(cp);
                    if (cw < 0) return ACX1_BAD_DATA;
                    if (!cw) continue;
                    if (cw == 2)
                    {
                        if (j == (uint_t) col_num - 1) break; // finish line if a wide char is in last column
                        ci[1].Attributes = a;
                        ci[1].Char.UnicodeChar = 0;
                    }
                }
                else
                {
                    cp = data[i][o];
                    if (cp == '\a')
                    {
                        crt_attr = data[i][o + 1];
                        a = prepare_attr(attrs[crt_attr].bg, attrs[crt_attr].fg,
                                         attrs[crt_attr].mode);
                        cw = 0;
                        l = 2;
                        continue;
                    }
                    if (cp < 0x20) return ACX1_BAD_DATA;
                    l = 1;
                    cw = 1;
                }
                ci->Char.UnicodeChar = (uint16_t) (cp >= 0x10000 ? 0 : cp);
                ci->Attributes = a;
            }
            if (j < col_num)
            {
                // crt_attr = 0;
                // a = prepare_attr(attrs[crt_attr].bg, attrs[crt_attr].fg,
                //                  attrs[crt_attr].mode);
                for (; j < col_num; ++j, ++ci)
                {
                    ci->Char.UnicodeChar = ' ';
                    ci->Attributes = a;
                }
            }

        }
        bs.Y = buf_rows;
        wr.Left = start_col;
        wr.Top = start_row;
        wr.Right = start_col + col_num - 1;
        wr.Bottom = start_row + buf_rows - 1;
        if (!WriteConsoleOutputW(hout, buf, bs, bc, &wr))
            return ACX1_TERM_IO_FAILED;
    }

    return 0;
}