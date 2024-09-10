bool INSTHYPOT::execute(void)
{
	bool result= false;
	VMREGTYPE val1,val2,sum= 0;
	if(machine.pop(val1)
		&& machine.pop(val2))
	{
		VMFLOAT f1= ffromi(val1);
		VMFLOAT f2= ffromi(val2);
		f1=(VMFLOAT) _hypot(f1,f2);
		sum= ifromf(f1);
		result= machine.push(sum);
	}
	
	return result;
}