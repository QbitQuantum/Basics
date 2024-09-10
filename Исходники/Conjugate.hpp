inline void
Conjugate( const DistMatrix<T,U,V>& A, DistMatrix<T,W,Z>& B )
{
#ifndef RELEASE
    PushCallStack("Conjugate");
#endif
    B = A;
    Conjugate( B );
#ifndef RELEASE
    PopCallStack();
#endif
}