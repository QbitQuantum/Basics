char *Illusion_ExcelFile::column_mbcs_name(long column_no)
{
    static unsigned char column_name[64];
    size_t str_len = 0;

    while (column_no > 0)
    {
        int num_data = column_no % 26;
        column_no /= 26;
        if (num_data == 0)
        {
            num_data = 26;
            column_no--;
        }
        //不知道这个对不，
        column_name[str_len] = (char)((num_data - 1) + ('A'));
        str_len++;
    }
    column_name[str_len] = '\0';
    //反转
    _mbsrev(column_name);

    return(char *) column_name;
}