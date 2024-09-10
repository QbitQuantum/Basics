String*
STRcpy(String *s1, String *s2)
{
     STRset(s1, STRget(s2));
     return(s1);
}