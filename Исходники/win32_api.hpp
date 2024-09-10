static inline bool move_file_ex(const char *source_filename, const char *destination_filename, unsigned long flags)
{
    return 0 != MoveFileExA(source_filename, destination_filename, flags);
}