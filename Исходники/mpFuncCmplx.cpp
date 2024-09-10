 //-----------------------------------------------------------------------
 void FunCmplxTanH::Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int)
 {
   cmplx_type v(a_pArg[0]->GetFloat(), a_pArg[0]->GetImag());
   *ret = tanh(v);
 }