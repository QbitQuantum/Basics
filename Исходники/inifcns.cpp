static ex abs_expl_derivative(const ex & arg, const symbol & s)
{
	ex diff_arg = arg.diff(s);
	return (diff_arg*arg.conjugate()+arg*diff_arg.conjugate())/2/abs(arg);
}