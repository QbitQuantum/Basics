int exec(int op, int a, int b) {
   int result;
const float PI =3.14159265;
if(op<0) {
	op = -op;
	int c;
	c =a;
	a =b;
	b =c;
	}
	switch (op){
	case 0:
		result =-a;
		break;
	case 1:
		result = a+b;
		break;
	case 2:
		result =a-b;
		break;
	case 3:
		result =a*b;
		break;
	case 4:
		result =a/b;
		break;
	case 5:
		result =abs(a);
		break;
	case 6:
		if((b<1)&&(a!=1)&&(a!=-1))
			result =0;
		else
			result = pow(a, b);
		break;
	case 7:
	case 13:
	case 77:
		result =a%b;
		break;
	case 8:
		if(a==b)
			result =0;
		else
			result =fmax(a, b);
		break;
	case 9:
		if(a==b)
			result =0;
		else
			result =fmin(a, b);
		break;
	case 10:
		switch (abs(b)%8){
				case 0:
					result =abs(a)*sizeof(char);
					break;
				case 1:
					result =abs(a)*sizeof(signed char);
					break;
				case 2:
					result =abs(a)*sizeof(short int);
					break;
				case 3:
					result =abs(a)*sizeof(unsigned int);
					break;
				case 4:
					result =abs(a)*sizeof(long int);
					break;
				case 5:
					result =abs(a)*sizeof(unsigned long long int);
					break;
				case 6:
					result =abs(a)*sizeof(float);
					break;
				case 7:
					result =abs(a)*sizeof(double);
					break;
		}
		break;
	case 11:
		if(b=2)
			result =0;
		else
			result =nearbyint(tg(a*PI)/(2-b));
		break;
	default:
		if(op<100){
			if((a == -1) || (b == -1))
				result =0;
			else
			result =((op / abs(a + 1)) + (op / abs(b + 1)));
		}
		else
			result =-1;
	}
   return result;
}