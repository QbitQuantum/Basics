int main()
{
	int i, n;
	Rectangle rect;
	Line line;
	
	scanf("%d", &n);
	
	for (i=0; i < n; i++) 
	{
		scanf("%d %d %d %d", &line.p1.x, &line.p1.y, &line.p2.x, &line.p2.y );
		
		scanf("%d %d %d %d", &rect.tleft.x, &rect.tleft.y, &rect.bright.x, &rect.bright.y );
		
		printf("%c\n", intersectRect(rect, line) ? 'T' : 'F' );
	}

	return 0;
}