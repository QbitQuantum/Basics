 Vector NeRegSuf::vectorize(bool minimal)const{
   reflect();
   Vector ans = xtx_.vectorize(minimal);
   ans.concat(xty_);
   ans.push_back(sumsqy);
   ans.push_back(n_);
   ans.push_back(sumy_);
   return ans;
 }