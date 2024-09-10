int sk_insert(STACK *st, char *data, int loc)
	{
	char **s;

	if(st == NULL) return 0;
	if (st->num_alloc <= st->num+1)
		{
		s=(char **)Realloc((char *)st->data,
			(unsigned int)sizeof(char *)*st->num_alloc*2);
		if (s == NULL)
			return(0);
		st->data=s;
		st->num_alloc*=2;
		}
	if ((loc >= (int)st->num) || (loc < 0))
		st->data[st->num]=data;
	else
		{
		int i;
		char **f,**t;

		f=(char **)st->data;
		t=(char **)&(st->data[1]);
		for (i=st->num; i>=loc; i--)
			t[i]=f[i];
			
#ifdef undef /* no memmove on sunos :-( */
		memmove( (char *)&(st->data[loc+1]),
			(char *)&(st->data[loc]),
			sizeof(char *)*(st->num-loc));
#endif
		st->data[loc]=data;
		}
	st->num++;
	st->sorted=0;
	return(st->num);
	}