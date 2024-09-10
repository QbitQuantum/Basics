double conversion(float w)
	{
		int punto_d,signo;
		char*cadena;
		double r,s;
		cadena=fcvt(w,4,&punto_d,&signo);
		r=atof(cadena);
		w=r/10000;
		if (signo==1)
		    w = w * (-1);
		return(w);
	}