void scan(A& x, char _ = ' ')
{
	while((x = getchar()) < '0');
	for(x -= '0'; '0' <= (_ = getchar()); x = (x << 3) + (x << 1) + _ - '0');
}