static void
netlist_style (LibraryMenuType *net, const char *style)
{
  free (net->Style);
  net->Style = STRDUP ((char *)style);
}