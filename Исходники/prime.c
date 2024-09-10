int main(int argc, char const *argv[])
{
	FILE * input;
	input = fopen('test.txt', "r");

	int n;
	long int lowerlim, upperlim;
	long int b, found, r, maxk, nextR, gcda, toir;
	double logresult, a, npowk;
	fscanf(input, "%d", &n);

	while(n > 0){
		fscanf(input, "%d %d", lowerlim, upperlim);
		while(lowerlim <= upperlim) {
			logresult = log2(lowerlim);
			for (b = 0; b < logresult; ++b) {
				a = pow(n, 1.0/b);
				if(a == (int )a){
					printf("%s\n", "composite");
					printf("%d\n", (int) a);
					found = 1;
					break;
				}
			}
			if (!found) {
				maxk = abs(pow(log2(lowerlim), 2));
				r = 2;
				nextR = 1;
				for (r = 2, nextR && r < maxk, r++ ){
					nextR = 0;
					for (k = 1; (!nextR) k <= maxk, ++k) {
						npowk = (int)pow(lowerlim, k);
						nextR = (((int)fmodf(npowk, r)) == 1 ||((int)fmodf(npowk, r)) == 0);
					}
				}
				r--;
				for (a = r; a > 1; a--) {
					gcda = gcd(a, lowerlim);
					if (gcda > 1 && gcd < lowerlim){
						found = 1;
						printf("%s\n", "composite");
						printf("%d\n", a);
						break;
					}
				}
			}

			if (!found) {
				if (n <= r) {
					found = 1;
					printf("%s\n", "prime");
					printf("%d\n", lowerlim);
				}
			}

			if (!found)	{
				toir = (int )floor(sqrt(phi(r))log(lowerlim));
				for(a = 1; a <= toir; a++) {
					if (/* condition */)
					{
						/* code */
					}
				}
			}

			lowerlim ++			
		}