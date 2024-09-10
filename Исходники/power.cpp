void
yypower(void)
{
	int n;

	p2 = pop();
	p1 = pop();

	// both base and exponent are rational numbers?

	if (isrational(p1) && isrational(p2)) {
		push(p1);
		push(p2);
		qpow();
		return;
	}

	// both base and exponent are either rational or double?

	if (isnum(p1) && isnum(p2)) {
		push(p1);
		push(p2);
		dpow();
		return;
	}

	if (istensor(p1)) {
		power_tensor();
		return;
	}

	if (p1 == symbol(E) && car(p2) == symbol(LOG)) {
		push(cadr(p2));
		return;
	}

	if (p1 == symbol(E) && isdouble(p2)) {
		push_double(exp(p2->u.d));
		return;
	}

	//	1 ^ a		->	1

	//	a ^ 0		->	1

	if (equal(p1, one) || iszero(p2)) {
		push(one);
		return;
	}

	//	a ^ 1		->	a

	if (equal(p2, one)) {
		push(p1);
		return;
	}

	//	(a * b) ^ c	->	(a ^ c) * (b ^ c)

	if (car(p1) == symbol(MULTIPLY)) {
		p1 = cdr(p1);
		push(car(p1));
		push(p2);
		power();
		p1 = cdr(p1);
		while (iscons(p1)) {
			push(car(p1));
			push(p2);
			power();
			multiply();
			p1 = cdr(p1);
		}
		return;
	}

	//	(a ^ b) ^ c	->	a ^ (b * c)

	if (car(p1) == symbol(POWER)) {
		push(cadr(p1));
		push(caddr(p1));
		push(p2);
		multiply();
		power();
		return;
	}

	//	(a + b) ^ n	->	(a + b) * (a + b) ...

	if (expanding && isadd(p1) && isnum(p2)) {
		push(p2);
		n = pop_integer();
        // this && n != 0x80000000 added by DDC
        // as it's not always the case that 0x80000000
        // is negative
		if (n > 1 && n != 0x80000000) {
			power_sum(n);
			return;
		}
	}

	//	sin(x) ^ 2n -> (1 - cos(x) ^ 2) ^ n

	if (trigmode == 1 && car(p1) == symbol(SIN) && iseveninteger(p2)) {
		push_integer(1);
		push(cadr(p1));
		cosine();
		push_integer(2);
		power();
		subtract();
		push(p2);
		push_rational(1, 2);
		multiply();
		power();
		return;
	}

	//	cos(x) ^ 2n -> (1 - sin(x) ^ 2) ^ n

	if (trigmode == 2 && car(p1) == symbol(COS) && iseveninteger(p2)) {
		push_integer(1);
		push(cadr(p1));
		sine();
		push_integer(2);
		power();
		subtract();
		push(p2);
		push_rational(1, 2);
		multiply();
		power();
		return;
	}

	// complex number? (just number, not expression)

	if (iscomplexnumber(p1)) {

		// integer power?

		// n will be negative here, positive n already handled

		if (isinteger(p2)) {

			//               /        \  n
			//         -n   |  a - ib  |
			// (a + ib)   = | -------- |
			//              |   2   2  |
			//               \ a + b  /

			push(p1);
			conjugate();
			p3 = pop();
			push(p3);
			push(p3);
			push(p1);
			multiply();
			divide();
			push(p2);
			negate();
			power();
			return;
		}

		// noninteger or floating power?

		if (isnum(p2)) {

#if 1			// use polar form
			push(p1);
			mag();
			push(p2);
			power();
			push_integer(-1);
			push(p1);
			arg();
			push(p2);
			multiply();
			push(symbol(PI));
			divide();
			power();
			multiply();

#else			// use exponential form
			push(p1);
			mag();
			push(p2);
			power();
			push(symbol(E));
			push(p1);
			arg();
			push(p2);
			multiply();
			push(imaginaryunit);
			multiply();
			power();
			multiply();
#endif
			return;
		}
	}

	if (simplify_polar())
		return;

	push_symbol(POWER);
	push(p1);
	push(p2);
	list(3);
}