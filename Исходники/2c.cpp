int main ()
{
	Libc x;
	x.seta("Die Katze");
	x.setb("The Cat");
	x.setc("Кошка");
	
	cout << x.geta() << endl;
	cout << x.getb() << endl;
	cout << x.getc() << endl;
}