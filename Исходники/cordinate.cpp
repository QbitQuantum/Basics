int main()
{
  int x , y;
  char temp; // garbage value of ,
  cout << "Enter cordinate x y in format x,y";
  cin >> x >> temp >> y;
  Coordinate a(x,y);
  cout << "Enter cordinate x y in format x,y";
  cin >> x >> temp >> y;
  Coordinate b(x,y);
  Vector v; 
  Coordinate c = v.add(a,b);
  cout << "The sum is ";
  c.display();
  cout << endl;
  Coordinate d = v.sub(a,b);
  cout << "The difference is";
  d.display();
  cout << endl;
  Coordinate p = v.mul(a,b);
  cout << "The product is";
  p.display();
  cout << endl;
  Coordinate q = v.div(a,b);
  cout << "The quotient is";
  q.display();
  cout << endl;
  return SUCCESS;
}