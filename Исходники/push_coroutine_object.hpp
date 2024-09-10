 void enter_()
 {
     holder< void > * hldr_from(
         reinterpret_cast< holder< void > * >(
             this->caller_.jump(
                 this->callee_,
                 reinterpret_cast< intptr_t >( this),
                 this->preserve_fpu() ) ) );
     this->callee_ = * hldr_from->ctx;
     if ( this->except_) rethrow_exception( this->except_);
 }