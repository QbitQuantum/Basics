int json_parse_double(const char *buf, double *retval)
{
  return (sscanf_s(buf, "%lf", retval)==1 ? 0 : 1);
}