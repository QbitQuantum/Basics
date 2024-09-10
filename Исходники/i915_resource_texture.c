static inline unsigned
align_nblocksy(enum pipe_format format, unsigned width, unsigned align_to)
{
   return align(util_format_get_nblocksy(format, width), align_to);
}