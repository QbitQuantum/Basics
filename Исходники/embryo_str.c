static Embryo_Cell
_embryo_str_snprintf(Embryo_Program *ep, Embryo_Cell *params)
{
   char *s1, *s2;
   int i, o;
   int inesc = 0;
   int insub = 0;
   int p, pnum;

   /* params[1] = buf */
   /* params[2] = bufsize */
   /* params[3] = format_string */
   /* params[4] = first arg ... */
   if (params[0] < (Embryo_Cell)(3 * sizeof(Embryo_Cell))) return 0;
   if (params[2] <= 0) return 0;
   STRGET(ep, s1, params[3]);
   if (!s1) return -1;
   s2 = alloca(params[2] + 1);
   if (!s2) return -1;
   s2[0] = 0;
   pnum = (params[0] / sizeof(Embryo_Cell)) - 3;
   for (p = 0, o = 0, i = 0; (s1[i]) && (o < (params[2] - 1)) && (p < (pnum + 1)); i++)
     {
	if ((!inesc) && (!insub))
	  {
	     if      (s1[i] == '\\') inesc = 1;
	     else if (s1[i] == '%')  insub = 1;
	     if ((!inesc) && (!insub))
	       {
		  s2[o] = s1[i];
		  o++;
	       }
	  }
	else
	  {
	     Embryo_Cell *cptr;

	     if (inesc)
	       {
		  switch (s1[i])
		    {
		     case 't':
		       s2[o] = '\t';
		       o++;
		       break;
		     case 'n':
		       s2[o] = '\n';
		       o++;
		       break;
		     default:
		       s2[o] = s1[i];
		       o++;
		       break;
		    }
		  inesc = 0;
	       }
	     if ((insub) && (s1[i] == '%')) pnum++;
	     if ((insub) && (p < pnum))
	       {
		  switch (s1[i])
		    {
		     case '%':
		       s2[o] = '%';
		       o++;
		       break;
		     case 'c':
		       cptr = embryo_data_address_get(ep, params[4 + p]);
		       if (cptr) s2[o] = (char)(*cptr);
		       p++;
		       o++;
		       break;
		     case 'i':
		     case 'd':
		     case 'x':
		     case 'X':
			 {
			    char fmt[10] = "";
			    char tmp[256] = "";
			    int l;

			    if      (s1[i] == 'i') strcpy(fmt, "%i");
			    else if (s1[i] == 'd') strcpy(fmt, "%d");
			    else if (s1[i] == 'x') strcpy(fmt, "%x");
			    else if (s1[i] == 'X') strcpy(fmt, "%08x");
			    cptr = embryo_data_address_get(ep, params[4 + p]);
			    if (cptr) snprintf(tmp, sizeof(tmp), fmt, (int)(*cptr));
			    l = strlen(tmp);
			    if ((o + l) > (params[2] - 1))
			      {
				 l = params[2] - 1 - o;
				 if (l < 0) l = 0;
				 tmp[l] = 0;
			      }
			    strcpy(s2 + o, tmp);
			    o += l;
			    p++;
			 }
		       break;
		     case 'f':
			 {
			    char tmp[256] = "";
			    int l;

			    cptr = embryo_data_address_get(ep, params[4 + p]);
			    if (cptr) snprintf(tmp, sizeof(tmp), "%f", (double)EMBRYO_CELL_TO_FLOAT(*cptr));
			    l = strlen(tmp);
			    if ((o + l) > (params[2] - 1))
			      {
				 l = params[2] - 1 - o;
				 if (l < 0) l = 0;
				 tmp[l] = 0;
			      }
			    strcpy(s2 + o, tmp);
			    o += l;
			    p++;
			 }
		       break;
		     case 's':
			 {
			    char *tmp;
			    int l;

			    STRGET(ep, tmp, params[4 + p]);
			    l = strlen(tmp);
			    if ((o + l) > (params[2] - 1))
			      {
				 l = params[2] - 1 - o;
				 if (l < 0) l = 0;
				 tmp[l] = 0;
			      }
			    strcpy(s2 + o, tmp);
			    o += l;
			    p++;
			 }
		       break;
		     default:
		       break;
		    }
		  insub = 0;
	       }
	     else if (insub)
	       insub = 0;
	  }
     }
   s2[o] = 0;

   STRSET(ep, params[1], s2);
   return o;
}