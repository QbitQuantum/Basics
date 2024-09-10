 void testNulls() {
     report(0,"testing null insertion");
     ConstString s;
     s += 'h';
     s += '\0';
     s += 'd';
     checkEqual((int)s.length(),3,"length with internal null");
     checkEqual(s[1],'\0',"null is there");
     checkEqual(s[2],'d',"after null");
 }