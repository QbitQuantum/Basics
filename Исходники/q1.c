main()
{
	float side, sq_area, rad, cir_area;
	
	printf ("Please enter the length of a side of the square.\n");
	scanf ("%f", &side);
	printf ("Please enter the radius of the circle.\n");
	scanf ("%f", &rad);
	
	square(&side, &sq_area);
	circle(&rad, &cir_area);
	
	printf ("\nThe area of the square is %f.", sq_area);
	printf ("\nThe area of the circle is %f.", cir_area);
	
	flushall();
	getchar();
}//end main()