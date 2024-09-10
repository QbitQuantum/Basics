 void strToUpper(std::string &str)
 {
     using std::toupper;
     using std::string;
     
     for(string::size_type i = 0, len = str.size(); i < len; ++i)
         str[i] = static_cast<string::value_type>(toupper(str[i]));
 }