int main() {
	char i, isPosExist, isAddOverflow, isMulOverflow;
	long k = 0, a, b, m, y, z;
	scanf("%ld %ld\n%ld\n", &a, &b, &m);
	for (i = 63; i >= 0; i--) {
		isPosExist = ((long) powl(2, i) & b) == (long) powl(2, i);
		isMulOverflow = k << 1 < k;
		z = isMulOverflow ? (k % m) * (2 % m) : k * 2;
		y = a * isPosExist;
		isAddOverflow = (z * y) < y && (z * y) < z;
		k = isAddOverflow ? (z % m) + (y % m) : z + y;
	}
	printf("%li", k % m);
	return 0;
}