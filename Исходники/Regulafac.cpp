/*double conversion(float w)
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
	}*/
double conversion(double w)
{
       cadena=fcvt(valor,5,&punto_d,&signo);
       r=atof(cadena);
       valor2=r/100000;
       if (signo==1)
       valor2 = valor2 * (-1);
       divi=valor2/0.0001;
       cadena2=fcvt(valor,4,&punto_d,&signo);
       valor3=atoi(cadena2);
       resta= valor3 - divi;
       if (resta > 0 )
       {
	     w= (valor3 - 1)* 0.0001;
       }
       if (resta < 0)
       {
	     w = valor3 * 0.0001;
       }
       return(w);
}