void
yybessely(void)
{
	double d;
	int n;

	N = pop();
	X = pop();

	push(N);
	n = pop_integer();

	if (isdouble(X) && n != (int) 0x80000000) {
		d = yn(n, X->u.d);
		push_double(d);
		return;
	}
	
	if (isnegativeterm(N)) {
		push_integer(-1);
		push(N);
		power();
		push_symbol(BESSELY);
		push(X);
		push(N);
		negate();
		list(3);
		multiply();
		return;
	}

	push_symbol(BESSELY);
	push(X);
	push(N);
	list(3);
	return;
}