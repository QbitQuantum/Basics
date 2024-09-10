 PhaseEnumerationCache
 ( const Matrix<Field>& B,
   const Matrix<Base<Field>>& d,
   const Matrix<Field>& N,
   const Matrix<Base<Field>>& normUpperBounds,
         Int batchSize=256,
         Int blocksize=32,
         bool useTranspose=true )
 : B_(B),
   d_(d),
   N_(N),
   normUpperBounds_(normUpperBounds),
   foundVector_(false),
   numQueued_(0),
   insertionBound_(normUpperBounds.Height()),
   blocksize_(blocksize),
   useTranspose_(useTranspose)
 { 
     Zeros( Y_, N.Height(), batchSize );   
     if( useTranspose )
         Transpose( N, NTrans_ );
 }