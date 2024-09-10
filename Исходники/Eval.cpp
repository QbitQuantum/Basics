 vector< symbol > operator()(const list& lst) const
 {
   vector< symbol > params(lst.size());
   transform(begin(lst), end(lst), begin(params), [](value v) {
       return apply_visitor(parameter_visitor(), v);
     });
   return params;
 }