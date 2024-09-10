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
		pt.SetX(x);
		pt.SetY(y);
		cout << pt.ToString();
		cout << "Please enter the value of x: " << endl;
		cin >> x;
		cout << "Please enter the value of y: " << endl;
		cin >> y;
		pt1.SetX(x);
		pt1.SetY(y);
		cout << pt1.ToString();
		//one deconstructor occurs before printing
		cout << "The distance between point 2 to point 1 is " << pt.Distance(pt1) << endl;
		/*before  copy constructor added, the number of constructors (2) and deconstructors(3) are not the same */
		//two deconstructors occurs here
	}