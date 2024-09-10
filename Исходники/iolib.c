/*
** Read a variable. On error put nil on stack.
** LUA interface:
**			variable = read ([format])
**
** O formato pode ter um dos seguintes especificadores:
**
**	s ou S -> para string
**	f ou F, g ou G, e ou E -> para reais
**	i ou I -> para inteiros
**
**	Estes especificadores podem vir seguidos de numero que representa
**	o numero de campos a serem lidos.
*/
static void io_read (void)
{
 lua_Object o = lua_getparam (1);
 if (o == NULL || !lua_isstring(o))	/* free format */
 {
  int c;
  char s[256];
  while (isspace(c=fgetc(in)))
   ;
  if (c == '\"')
  {
   int c, n=0;
   while((c = fgetc(in)) != '\"')
   {
    if (c == EOF)
    {
     lua_pushnil ();
     return;
    }
    s[n++] = c;
   }
   s[n] = 0;
  }
  else if (c == '\'')
  {
   int c, n=0;
   while((c = fgetc(in)) != '\'')
   {
    if (c == EOF)
    {
     lua_pushnil ();
     return;
    }
    s[n++] = c;
   }
   s[n] = 0;
  }
  else
  {
   char *ptr;
   double d;
   ungetc (c, in);
   if (fscanf (in, "%s", s) != 1)
   {
    lua_pushnil ();
    return;
   }
   d = strtod (s, &ptr);
   if (!(*ptr))
   {
    lua_pushnumber (d);
    return;
   }
  }
  lua_pushstring (s);
  return;
 }
 else				/* formatted */
 {
  char *e = lua_getstring(o);
  char t;
  int  m=0;
  while (isspace(*e)) e++;
  t = *e++;
  while (isdigit(*e))
   m = m*10 + (*e++ - '0');
  
  if (m > 0)
  {
   char f[80];
   char s[256];
   sprintf (f, "%%%ds", m);
   if (fgets (s, m, in) == NULL)
   {
    lua_pushnil();
    return;
   }
   else
   {
    if (s[strlen(s)-1] == '\n')
     s[strlen(s)-1] = 0;
   }
   switch (tolower(t))
   {
    case 'i':
    {
     long int l;
     sscanf (s, "%ld", &l);
     lua_pushnumber(l);
    }
    break;
    case 'f': case 'g': case 'e':
    {
     float f;
     sscanf (s, "%f", &f);
     lua_pushnumber(f);
    }
    break;
    default: 
     lua_pushstring(s); 
    break;
   }
  }
  else
  {
   switch (tolower(t))
   {
    case 'i':
    {
     long int l;
     if (fscanf (in, "%ld", &l) == EOF)
       lua_pushnil();
       else lua_pushnumber(l);
    }
    break;
    case 'f': case 'g': case 'e':
    {
     float f;
     if (fscanf (in, "%f", &f) == EOF)
       lua_pushnil();
       else lua_pushnumber(f);
    }
    break;
    default: 
    {
     char s[256];
     if (fscanf (in, "%s", s) == EOF)
       lua_pushnil();
       else lua_pushstring(s);
    }
    break;
   }
  }
 }
}