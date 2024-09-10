 string addBinary(string a, string b) {
     if(a.length() < b.length())
         a.swap(b);
     
     findSum(a, b);
     
     return a;
 }