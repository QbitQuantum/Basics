static int get_last_char_offset(char *fat_string)
{
    int i = 0;

    for (i = strlen(fat_string) - 1; i >= 0; i--) {
        if (ISGRAPH((int) *(fat_string + i)))
            return (i + 1);
    }

    return (strlen(fat_string));
}