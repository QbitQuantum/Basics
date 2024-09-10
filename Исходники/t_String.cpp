int
main(int argc, char** argv)
{
   String a;
   a = "Testing...";
   cout << a << endl;
   cout << "length: " << a.length() << endl;
   cout << "capacity: " << a.capacity() << endl;

   a = a + "one two three";
   cout << a << endl;
   cout << "length: " << a.length() << endl;
   cout << "capacity: " << a.capacity() << endl;

   a = "stuff on the front:" + a;
   cout << a << endl;
   cout << "length: " << a.length() << endl;
   cout << "capacity: " << a.capacity() << endl;

   long intval = 0;
   if (String("32").parseInt(intval))
      cout << "Converting '32' to int: " << intval << endl;
   else
      cout << "Error converting string to int.\n";

   double doubleval = 0.0;
   String("3.141592654").parseDouble(doubleval);
   cout << "Converting 3.141592654 to double: " << doubleval << endl;

   long hexval = 0;
   if (String("0x34ab").parseHex(hexval))
      cout << "Converting 0x34ab to " << hexval << " (Should be 13483)" << endl;
   else
      cout << "Hex conversion failed.\n";
   
   

   String tflag("true");
   String fflag("false");

   bool boolval;

   tflag.parseBool(boolval);
   if (boolval)
      cout << "This should have been true (and was)" << endl;
   else
      cout << "tflag was false and should have been true." << endl;

   fflag.parseBool(boolval);
   if (boolval)
      cout << "fflag should have been false and wasn't." << endl;
   else
      cout << "fflag was false and should have been." << endl;
   
   char c;
   a.charAt(3, c);
   cout << "\nCharacter at position 3: '" << c << "' \n";

   String b("cat");
   String d = "cat";

   if (b == d)
      cout << "Yup, equal.\n";
   else
      cout << "Nope, not equal.\n";

   if (b == "fark")
      cout << b << " is less than fark\n";

   cout << a.toLower() << endl;
   cout << a.toUpper() << endl;

   cout << "Substring..." << endl;
   String substr_test = "this is a weird string. Much odd.";
   cout << substr_test.substring(4, 4) << endl;
   
   cout << "Regular Expressions\n";
   String astring = "This is a test.";
   if (astring.matches("is a"))
      cout << "   Matched!\n";
   else
      cout << "   Didn't match.\n";

   String csvstuff = "3.1415     2.71828   42   testing";
   ArrayList<String> fields = csvstuff.split(" +");
}