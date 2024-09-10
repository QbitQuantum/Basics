int main()
{
  cout << clock() << '\n';
  try
  {
    f(0);
  }
  catch(myErr)
  {
  }
  cout << clock() << '\n';
  try
  {
    f(1);
  }
  catch(myErr)
  {
  }
  cout << clock() << '\n';

 
}