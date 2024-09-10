void do_for (void)
/***** do_for
	do a for command in a UDF.
	for i=value to value step value; .... ; end
*****/
{	int h,signum;
	char name[16],*jump;
	header *hd,*init,*end,*step;
	double vend,vstep;
	struct { header hd; double value; } rv;
	if (!udfon)
	{	output("For only allowed in functions!\n"); error=57; return;
	}
	rv.hd.type=s_real; *rv.hd.name=0;
	rv.hd.size=sizeof(header)+sizeof(double); rv.value=0.0;
	scan_space(); scan_name(name); if (error) return;
	kill_local(name);
	newram=endlocal;
	hd=new_reference(&rv.hd,name); if (error) return;
	endlocal=newram=(char *)hd+hd->size;
	scan_space(); if (*next!='=')
	{	output("Syntax error in for.\n"); error=71; goto end;
	}
	next++; init=scan(); if (error) goto end;
	init=getvalue(init); if (error) goto end;
	if (init->type!=s_real)
	{	output("Startvalue must be real!\n"); error=72; goto end;
	}
	rv.value=*realof(init);
	scan_space(); if (strncmp(next,"to",2))
	{	output("Endvalue missing in for!\n"); error=73; goto end;
	}
	next+=2;
	end=scan(); if (error) goto end;
	end=getvalue(end); if (error) goto end;
	if (end->type!=s_real)
	{	output("Endvalue must be real!\n"); error=73; goto end;
	}
	vend=*realof(end);
	scan_space();
	if (!strncmp(next,"step",4))
	{	next+=4;
		step=scan(); if (error) goto end;
		step=getvalue(step); if (error) goto end;
		if (step->type!=s_real)
		{	output("Stepvalue must be real!\n"); error=73; goto end;
		}
		vstep=*realof(step);
	}
	else vstep=1.0;
	signum=(vstep>=0)?1:-1;
	vend=vend+signum*epsilon;
	if (signum>0 && rv.value>vend) { scan_end(); goto end; }
	else if (signum<0 && rv.value<vend) { scan_end(); goto end; }
	newram=endlocal;
	scan_space(); if (*next==';' || *next==',') next++;
	jump=next;
	while (!error)
	{	if (*next==1)
		{	output("End missing!\n");
			error=401; goto end;
		}
		h=command();
		if (udfon!=1 || h==c_return) break;
		if (h==c_break) { scan_end(); break; }
		if (h==c_end)
		{	rv.value+=vstep;
			if (signum>0 && rv.value>vend) break;
			else if (signum<0 && rv.value<vend) break;
			else next=jump;
			if (test_key()==escape)
			{   output("User interrupted!\n");
				error=1; break;
			}
		}
	}
	end : kill_local(name);
}