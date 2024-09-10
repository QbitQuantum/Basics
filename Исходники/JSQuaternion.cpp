 //! \verbatim
 //! Quaternion Quaternion.inverse()
 //! \endverbatim
 void Quaternion::jsInverse( const FunctionCallbackInfo<v8::Value>& args )
 {
   Quaternion* ptr = unwrap( args.Holder() );
   args.GetReturnValue().Set( Quaternion::newFrom( ptr->Inverse() ) );
 }