void main(){
	double x, y;
	int index;
	cout << "Please enter the section (1 or 2) you want " << endl;
	cin >> index;
	if (index == 1){
		Point pt;//constructor occurs here
		Point pt1;//constructor occurs here
		cout << "Please enter the value of x: " << endl;
		cin >> x;
		cout << "Please enter the value of y: " << endl;
		cin >> y;
		pt.X(x);
		pt.Y(y);
		cout << pt.ToString();
		cout << "Please enter the value of x: " << endl;
		cin >> x;
		cout << "Please enter the value of y: " << endl;
		cin >> y;
		pt1.X(x);
		pt1.Y(y);
		cout << pt1.ToString();
		cout << "The distance between point 1 to origin is " << pt.Distance() << endl;
		cout << "The distance between point 2 to point 1 is " << pt.Distance(pt1) << endl;
		/*the number of constructors (2) and deconstructors(2) are the same since we pass the point by reference*/
		//two deconstructors occurs here
	}