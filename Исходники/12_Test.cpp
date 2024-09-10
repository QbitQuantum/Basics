void main()
{
	Rect r (10,10,20,20);

	r.InflateRect(10, 10);
	r.print();

	int s = r.GetArea();

	if ( r.PtInRect(15, 15))
		cout << "(15,15) is In r" << endl;
}