 void copy_results()
 {
   derivatives_.setZero();
   for(size_t i=0; i<expressions_.size(); ++i)
   {
     values_(i, 0) = expressions_[i]->value();
     for(size_t j=0; j<expressions_[i]->number_of_derivatives(); ++j)
       derivatives_(i,j) = expressions_[i]->derivative(j);
   }
 }