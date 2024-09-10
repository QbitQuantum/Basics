 void initialize( const Vector<Real> &x, const Vector<Real> &s, const Vector<Real> &g,
                  Objective<Real> &obj, BoundConstraint<Real> &con ) {
   LineSearch<Real>::initialize(x,s,g,obj,con);
   xnew_ = x.clone();
   btls_->initialize(x,s,g,obj,con);
 }