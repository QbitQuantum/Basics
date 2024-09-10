 string add(string num1, string num2) {
     if (num1.length() < num2.length()) {
         num1.swap(num2);
     }
     char c = '0';
     string result = "";
     int len1 = num1.length(), len2 = num2.length();
     for (int i = 0; i < len2; i ++) {
         char a = num1[len1 - i - 1], b = num2[len2 - i - 1];
         result = add(a, b, c) + result;
     }
     for (int i = len1 - len2 - 1; i >= 0; i --) {
         result = add(num1[i], '0', c) + result;
     }
     if (c != '0') {
         result = c + result;
     }
     return result;
 }