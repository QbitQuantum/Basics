string
uppercasify P1C(const_string, s)
{
  string target;
  string ret = xstrdup (s);
  
  for (target = ret; *target; target++)
    {
      *target = TOUPPER (*target);
    }
  
  return ret;
}