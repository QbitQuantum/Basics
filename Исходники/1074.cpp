 void print_real_number(const string& s,int N)
 {
      static const int MAXLENGTH=200;
      static const int MAXN=100;
      int position_of_e=std::string::npos;
      if (s.find("e")!=std::string::npos) position_of_e=s.find("e");
      if (s.find("E")!=std::string::npos) position_of_e=s.find("E");
      
      string simple_real_number_part;
      int value_of_e;
      if (position_of_e!=std::string::npos)
      {
         simple_real_number_part=s.substr(0,position_of_e);
         stringstream
         in(s.substr(position_of_e+1,s.length()-(position_of_e+1)));
         double get;
         in>>get;
         if (get>MAXLENGTH) value_of_e=MAXLENGTH;
         else if (get<-MAXLENGTH) value_of_e=-MAXLENGTH;
         else value_of_e=floor(get+0.5);
      }