int main()
{
	double sp, arie, a, b, c, mid;


	scanf("%d %d %d %d %d %d %d", &A.x, &A.y, &B.x, &B.y, &C.x, &C.y, &L);

	a = dist(B, C);
	b = dist(A, C);
	c = dist(A, B);
	
	Mid.x = (A.x + B.x) / 2;
	Mid.y = (A.y + B.y) / 2;

	mid = dist(C, Mid);


	sp = (a + b + c) / 2;

	arie = sqrtl(sp * (sp - a) * (sp - b) * (sp - c));

	if (c == 0)
		Dif = b;
	else
	if (mid >= min(a, b) && mid <= max(a, b))
		Dif = min(a, b);
	else
		Dif = 2 * arie / c;

	Dif = (Dif < L) ? 0 : Dif - L;

	LMax = max(a, b);
	LMax = (LMax < L) ? 0 : LMax - L;

	printf("%.2lf\n%.2lf\n", Dif, LMax);


	return 0;
}