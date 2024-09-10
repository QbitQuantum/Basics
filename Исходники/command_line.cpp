 // Lowercase字符串. 使用lowercase转化字符.
 static void Lowercase(std::string* parameter)
 {
     transform(parameter->begin(), parameter->end(),
         parameter->begin(), tolower);
 }