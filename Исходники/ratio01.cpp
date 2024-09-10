int main(){
	Ratio x;
	x.assign(22,7);
	cout << "x = ";
	x.print();
	cout << " = " << x.convert() << endl;
	x.invert();
	cout << "1/x = "; x.print();
	cout << endl;
}