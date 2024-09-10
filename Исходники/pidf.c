time_t xml_parse_dateTime(char* xml_time_str)
{
	struct tm tm;
	char * p;
	int h, m;
	char h1, h2, m1, m2;
	int sign= 1;
	signed int timezone_diff= 0;

	p= strptime(xml_time_str, "%F", &tm);
	if(p== NULL)
	{
		printf("error: failed to parse time\n");
		return 0;
	}
	p++;
	p= strptime(p, "%T", &tm);
	if(p== NULL)
	{
		printf("error: failed to parse time\n");
		return 0;
	}
	
	if(*p== '\0')
		goto done;

	if(*p== '.')
	{
		p++;
		/* read the fractionar part of the seconds*/
		while(*p!= '\0' && *p>= '0' && *p<= '9')
		{
			p++;
		}
	}

	if(*p== '\0')
		goto done;

	
	/* read time zone */

	if(*p== 'Z')
	{
		goto done;
	}

	if(*p== '+')
		sign= -1;

	p++;

	if(sscanf(p, "%c%c:%c%c", &h1, &h2, &m1, &m2) < 0) {
		printf("error: failed to parse time\n");
		return 0;
	}
	
	h= (h1- '0')*10+ h2- '0';
	m= (m1- '0')*10+ m2- '0';

	timezone_diff= sign* ((m+ h* 60)* 60);

done:
	return (mktime(&tm) + timezone_diff);	
}