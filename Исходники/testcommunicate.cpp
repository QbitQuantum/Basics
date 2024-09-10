int main()
{   char a;
   Tserial *com;
   com = new Tserial();
   com->connect("COM11", 9600, spNONE);                            //check com port
   cvWaitKey(5000);
   while(1)
   {       
           a=com->getChar();
           cout<<a<<endl;
           //cvWaitKey(1000);
          // cout<<"i";
   }
}