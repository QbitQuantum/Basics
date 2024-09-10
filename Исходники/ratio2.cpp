int main () {
	Ratio x (22, 7);
	cout << "x= ";
	x.print();
	cout << "x= " << x.convert() << endl;
	x.invert();
	cout << "x/1= ";
	x.print();
	cout << endl;

}