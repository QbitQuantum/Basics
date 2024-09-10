int main()
{
	const time t1(1, 10, 35), t2(0, 55, 44);
	time t3;
	time t4(0,1,1);

	// add two times to t3 and t4
	t3.add(t1, t2);
	t4.add(t1, t2);
	cout << "Time 1: "; t1.display();
	cout << "Time 2: "; t2.display();
	cout << "Time 3 = time 1 + time 2: "; t3.display();
	cout << "Time 4 = time 1 + time 2: "; t4.display();
	time t5 = t1+t2;
	cout << "Time 5 = time 1 + time 2: "; t5.display();

	system("pause");
	return 0;
}