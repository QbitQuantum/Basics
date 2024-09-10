void AltJacobi::Table::operator () (unsigned k,QType result[ /* p */ ]) const
 {
  for(unsigned i=0,p=this->p; i<p ;i++) result[i]=coeff(k,i,p);
  
  Normalize(result,p);
 }