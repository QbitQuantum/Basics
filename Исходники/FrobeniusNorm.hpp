inline typename Base<F>::type
internal::FrobeniusNorm( const DistMatrix<F,MC,MR>& A )
{
#ifndef RELEASE
    PushCallStack("internal::FrobeniusNorm");
#endif
    typedef typename Base<F>::type R;

    R localScale = 0;
    R localScaledSquare = 1;
    for( int jLocal=0; jLocal<A.LocalWidth(); ++jLocal )
    {
        for( int iLocal=0; iLocal<A.LocalHeight(); ++iLocal )
        {
            const R alphaAbs = Abs(A.GetLocalEntry(iLocal,jLocal));
            if( alphaAbs != 0 )
            {
                if( alphaAbs <= localScale )
                {
                    const R relScale = alphaAbs/localScale;
                    localScaledSquare += relScale*relScale;
                }
                else
                {
                    const R relScale = localScale/alphaAbs;
                    localScaledSquare = localScaledSquare*relScale*relScale + 1;
                    localScale = alphaAbs; 
                }
            }
        }
    }

    // Find the maximum relative scale
    R scale;
    mpi::AllReduce( &localScale, &scale, 1, mpi::MAX, A.Grid().VCComm() );

    R norm = 0;
    if( scale != 0 )
    {
        // Equilibrate our local scaled sum to the maximum scale
        R relScale = localScale/scale;
        localScaledSquare *= relScale*relScale;

        // The scaled square is now simply the sum of the local contributions
        R scaledSquare;
        mpi::AllReduce
        ( &localScaledSquare, &scaledSquare, 1, mpi::SUM, A.Grid().VCComm() );

        norm = scale*Sqrt(scaledSquare);
    }
#ifndef RELEASE
    PopCallStack();
#endif
    return norm;
}