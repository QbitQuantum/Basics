void main()
{
	using namespace std;

	const Point cp(1.5, 3.9);           //creates a constant Point variable called cp
	
	 cp.ToString();      // output onto screen the ToString() function of cp

     cout<<"The distance between this point and the origin is :"<<cp.Distance()<<endl;
	 //prints the distance of Point cp and origin onto screen
	 
	 
	 cout<<"For the source code cp.X(0.3):, the x coordinate is : "<<cp.X(0.3)<<endl;
	 //output the x-coordinate of cp as 0.3
	 system("PAUSE");


}