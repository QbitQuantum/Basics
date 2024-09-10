int main()
{
  Set a(63), c(63);
  Set d(65);

  a.print(cout); cout << endl;
  a.add(1); a.add(5);
  a.print(cout); cout << endl;

  Set b = a;
  b.add(3); 
  if (b.has(3))
	b.remove(3);
  if (b.has(5))
	b.add(6);
  //b.has(-10);
  //b.add(64);
  //b.remove(64);
  b.print(cout); cout << endl;
  
  c.add(8);
  c.add(a);
  c.print(cout); cout << endl;
  
  //d.add(a);
  
  a.complement();
  a.print(cout); cout << endl;
  
  cout << "Finished\n";
}