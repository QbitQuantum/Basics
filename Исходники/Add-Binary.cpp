 string addBinary(string a, string b) {
     //swap a and b if a is shorter than b
     //we will store the answer in a
     if(a.length() < b.length())
         a.swap(b);
     //@l1 the index of a[]
     //@l2 the index of b[]
     int l1 = a.length()-1;
     int l2 = b.length()-1;
     int add = 0;
     //process the common bits
     for(; l1>=0 && l2>=0; --l1,--l2)
         {
             int c = a[l1]-'0';
             int d = b[l2]-'0';
             int e = c+d+add;
             a[l1] = e%2+'0';
             add = e/2;
         }
     //process the last bits in a
     for(; l1>=0; --l1)
         {
             int c = a[l1]-'0';
             int e = c+add;
             a[l1] = e%2+'0';
             add = e/2;
         }
     //insert an 1 at the first position
     if(1==add)
         a.insert(0,1,'1');
     return a;
 }