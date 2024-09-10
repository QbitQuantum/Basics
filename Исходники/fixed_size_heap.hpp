 void get_sorted(std::vector<T>& v) const {
   std::vector<T> vec(data_);
   std::sort(vec.begin(), vec.end(), comp_);
   v.swap(vec);
 }