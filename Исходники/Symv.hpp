inline void
Symv
( UpperOrLower uplo,
  T alpha, const DistMatrix<T>& A,
           const DistMatrix<T>& x,
  T beta,        DistMatrix<T>& y,
  bool conjugate=false )
{
#ifndef RELEASE
    CallStackEntry entry("Symv");
    if( A.Grid() != x.Grid() || x.Grid() != y.Grid() )
        throw std::logic_error
        ("{A,x,y} must be distributed over the same grid");
    if( A.Height() != A.Width() )
        throw std::logic_error("A must be square");
    if( ( x.Width() != 1 && x.Height() != 1 ) ||
        ( y.Width() != 1 && y.Height() != 1 ) )
        throw std::logic_error("x and y are assumed to be vectors");
    const int xLength = ( x.Width()==1 ? x.Height() : x.Width() );
    const int yLength = ( y.Width()==1 ? y.Height() : y.Width() );
    if( A.Height() != xLength || A.Height() != yLength )
    {
        std::ostringstream msg;
        msg << "Nonconformal Symv: \n"
            << "  A ~ " << A.Height() << " x " << A.Width() << "\n"
            << "  x ~ " << x.Height() << " x " << x.Width() << "\n"
            << "  y ~ " << y.Height() << " x " << y.Width() << "\n";
        throw std::logic_error( msg.str() );
    }
#endif
    const Grid& g = A.Grid();

    if( x.Width() == 1 && y.Width() == 1 )
    {
        // Temporary distributions
        DistMatrix<T,MC,STAR> x_MC_STAR(g), z_MC_STAR(g);
        DistMatrix<T,MR,STAR> x_MR_STAR(g), z_MR_STAR(g);
        DistMatrix<T,MR,MC  > z_MR_MC(g);
        DistMatrix<T> z(g);

        // Begin the algoritm
        Scale( beta, y );
        x_MC_STAR.AlignWith( A );
        x_MR_STAR.AlignWith( A );
        z_MC_STAR.AlignWith( A );
        z_MR_STAR.AlignWith( A );
        z.AlignWith( y );
        Zeros( z_MC_STAR, y.Height(), 1 );
        Zeros( z_MR_STAR, y.Height(), 1 );
        //--------------------------------------------------------------------//
        x_MC_STAR = x;
        x_MR_STAR = x_MC_STAR;
        if( uplo == LOWER )
        {
            internal::LocalSymvColAccumulateL
            ( alpha, A, x_MC_STAR, x_MR_STAR, z_MC_STAR, z_MR_STAR, conjugate );
        }
        else
        {
            internal::LocalSymvColAccumulateU
            ( alpha, A, x_MC_STAR, x_MR_STAR, z_MC_STAR, z_MR_STAR, conjugate );
        }

        z_MR_MC.SumScatterFrom( z_MR_STAR );
        z = z_MR_MC;
        z.SumScatterUpdate( T(1), z_MC_STAR );
        Axpy( T(1), z, y );
        //--------------------------------------------------------------------//
        x_MC_STAR.FreeAlignments();
        x_MR_STAR.FreeAlignments();
        z_MC_STAR.FreeAlignments();
        z_MR_STAR.FreeAlignments();
        z.FreeAlignments();
    }
    else if( x.Width() == 1 )
    {
        // Temporary distributions
        DistMatrix<T,MC,STAR> x_MC_STAR(g), z_MC_STAR(g);
        DistMatrix<T,MR,STAR> x_MR_STAR(g), z_MR_STAR(g);
        DistMatrix<T,MR,MC  > z_MR_MC(g);
        DistMatrix<T> z(g), zTrans(g);

        // Begin the algoritm
        Scale( beta, y );
        x_MC_STAR.AlignWith( A );
        x_MR_STAR.AlignWith( A );
        z_MC_STAR.AlignWith( A );
        z_MR_STAR.AlignWith( A );
        z.AlignWith( y );
        z_MR_MC.AlignWith( y );
        Zeros( z_MC_STAR, y.Width(), 1 );
        Zeros( z_MR_STAR, y.Width(), 1 );
        //--------------------------------------------------------------------//
        x_MC_STAR = x;
        x_MR_STAR = x_MC_STAR;
        if( uplo == LOWER )
        {
            internal::LocalSymvColAccumulateL
            ( alpha, A, x_MC_STAR, x_MR_STAR, z_MC_STAR, z_MR_STAR, conjugate );
        }
        else
        {
            internal::LocalSymvColAccumulateU
            ( alpha, A, x_MC_STAR, x_MR_STAR, z_MC_STAR, z_MR_STAR, conjugate );
        }

        z.SumScatterFrom( z_MC_STAR );
        z_MR_MC = z;
        z_MR_MC.SumScatterUpdate( T(1), z_MR_STAR );
        Transpose( z_MR_MC, zTrans );
        Axpy( T(1), zTrans, y );
        //--------------------------------------------------------------------//
        x_MC_STAR.FreeAlignments();
        x_MR_STAR.FreeAlignments();
        z_MC_STAR.FreeAlignments();
        z_MR_STAR.FreeAlignments();
        z.FreeAlignments();
        z_MR_MC.FreeAlignments();
    }
    else if( y.Width() == 1 )
    {
        // Temporary distributions
        DistMatrix<T,STAR,MC> x_STAR_MC(g), z_STAR_MC(g);
        DistMatrix<T,STAR,MR> x_STAR_MR(g), z_STAR_MR(g);
        DistMatrix<T,MR,  MC> z_MR_MC(g);
        DistMatrix<T> z(g), zTrans(g);

        // Begin the algoritm
        Scale( beta, y );
        x_STAR_MC.AlignWith( A );
        x_STAR_MR.AlignWith( A );
        z_STAR_MC.AlignWith( A );
        z_STAR_MR.AlignWith( A );
        z.AlignWith( y );
        z_MR_MC.AlignWith( y );
        Zeros( z_STAR_MC, 1, y.Height() );
        Zeros( z_STAR_MR, 1, y.Height() );
        //--------------------------------------------------------------------//
        x_STAR_MR = x;
        x_STAR_MC = x_STAR_MR;
        if( uplo == LOWER )
        {
            internal::LocalSymvRowAccumulateL
            ( alpha, A, x_STAR_MC, x_STAR_MR, z_STAR_MC, z_STAR_MR, conjugate );
        }
        else
        {
            internal::LocalSymvRowAccumulateU
            ( alpha, A, x_STAR_MC, x_STAR_MR, z_STAR_MC, z_STAR_MR, conjugate );
        }

        z.SumScatterFrom( z_STAR_MR );
        z_MR_MC = z;
        z_MR_MC.SumScatterUpdate( T(1), z_STAR_MC );
        Transpose( z_MR_MC, zTrans );
        Axpy( T(1), zTrans, y );
        //--------------------------------------------------------------------//
        x_STAR_MC.FreeAlignments();
        x_STAR_MR.FreeAlignments();
        z_STAR_MC.FreeAlignments();
        z_STAR_MR.FreeAlignments();
        z.FreeAlignments();
        z_MR_MC.FreeAlignments();
    }
    else
    {
        // Temporary distributions
        DistMatrix<T,STAR,MC> x_STAR_MC(g), z_STAR_MC(g);
        DistMatrix<T,STAR,MR> x_STAR_MR(g), z_STAR_MR(g);
        DistMatrix<T,MR,  MC> z_MR_MC(g);
        DistMatrix<T> z(g);

        // Begin the algoritm
        Scale( beta, y );
        x_STAR_MC.AlignWith( A );
        x_STAR_MR.AlignWith( A );
        z_STAR_MC.AlignWith( A );
        z_STAR_MR.AlignWith( A );
        z.AlignWith( y );
        z_MR_MC.AlignWith( y );
        Zeros( z_STAR_MC, 1, y.Width() );
        Zeros( z_STAR_MR, 1, y.Width() );
        //--------------------------------------------------------------------//
        x_STAR_MR = x;
        x_STAR_MC = x_STAR_MR;
        if( uplo == LOWER )
        {
            internal::LocalSymvRowAccumulateL
            ( alpha, A, x_STAR_MC, x_STAR_MR, z_STAR_MC, z_STAR_MR, conjugate );
        }
        else
        {
            internal::LocalSymvRowAccumulateU
            ( alpha, A, x_STAR_MC, x_STAR_MR, z_STAR_MC, z_STAR_MR, conjugate );
        }

        z_MR_MC.SumScatterFrom( z_STAR_MC );
        z = z_MR_MC;
        z.SumScatterUpdate( T(1), z_STAR_MR );
        Axpy( T(1), z, y );
        //--------------------------------------------------------------------//
        x_STAR_MC.FreeAlignments();
        x_STAR_MR.FreeAlignments();
        z_STAR_MC.FreeAlignments();
        z_STAR_MR.FreeAlignments();
        z.FreeAlignments();
        z_MR_MC.FreeAlignments();
    }
}