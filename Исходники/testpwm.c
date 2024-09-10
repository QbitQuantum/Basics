/*****
 * voltstostrng() - converts volts to a fixed format string
 * 
 * accepts an float voltage reading and turns it into a 5 character string
 * of the following format:
 *		(+/-)x.yy 
 * where (+/-) is the sign, x is the integer part of the voltage and yy is
 * the decimal part of the voltage.
 *	
 * NOTE:  Assumes that s points to an array of at least 6 bytes.	
 *****/
 void	voltstostrng(float v, char* s)
 {
	float	dpf, ipf;
	u32		dpi;	
	u32		ones, tenths, hundredths;

	 // form the fixed digits 
	 dpf = modff(v, &ipf);
	 dpi = dpf * 100;
	 ones = abs(ipf) + '0';
	 tenths = (dpi / 10) + '0';
	 hundredths = (dpi - ((tenths - '0') * 10)) + '0';
	 
	 // form the string and return
	 if (ipf == 0 && dpf == 0)
	 {
	 	*s++ = ' ';
	 }
	 else	
	 { 
	 	*s++ = ipf >= 0 ? '+' : '-';
	 }
	 *s++ = (char) ones;
	 *s++ = '.';
	 *s++ = (char) tenths;
	 *s++ = (char) hundredths;
	 *s   = 0;
	 return;
 };