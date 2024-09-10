void LUMod
( Matrix<F>& A,
        Permutation& P, 
  const Matrix<F>& u,
  const Matrix<F>& v,
  bool conjugate,
  Base<F> tau )
{
    DEBUG_CSE
    typedef Base<F> Real;
    const Int m = A.Height();
    const Int n = A.Width();
    const Int minDim = Min(m,n);
    if( minDim != m )
        LogicError("It is assumed that height(A) <= width(A)");
    if( u.Height() != m || u.Width() != 1 )
        LogicError("u is expected to be a conforming column vector");
    if( v.Height() != n || v.Width() != 1 )
        LogicError("v is expected to be a conforming column vector");

    // w := inv(L) P u
    auto w( u );
    P.PermuteRows( w );
    Trsv( LOWER, NORMAL, UNIT, A, w );

    // Maintain an external vector for the temporary subdiagonal of U
    Matrix<F> uSub;
    Zeros( uSub, minDim-1, 1 );

    // Reduce w to a multiple of e0
    for( Int i=minDim-2; i>=0; --i )
    {
        // Decide if we should pivot the i'th and i+1'th rows of w
        const F lambdaSub = A(i+1,i);
        const F ups_ii = A(i,i); 
        const F omega_i = w(i);
        const F omega_ip1 = w(i+1);
        const Real rightTerm = Abs(lambdaSub*omega_i+omega_ip1);
        const bool pivot = ( Abs(omega_i) < tau*rightTerm );

        const Range<Int> indi( i, i+1 ),
                         indip1( i+1, i+2 ),
                         indB( i+2, m ),
                         indR( i+1, n );

        auto lBi   = A( indB,   indi   );
        auto lBip1 = A( indB,   indip1 );
        auto uiR   = A( indi,   indR   );
        auto uip1R = A( indip1, indR   );

        if( pivot )
        {
            // P := P_i P
            P.Swap( i, i+1 );

            // Simultaneously perform 
            //   U := P_i U and
            //   L := P_i L P_i^T
            //
            // Then update
            //     L := L T_{i,L}^{-1},
            //     U := T_{i,L} U, 
            //     w := T_{i,L} P_i w,
            // where T_{i,L} is the Gauss transform which zeros (P_i w)_{i+1}.
            // 
            // More succinctly,
            //     gamma    := w(i) / w(i+1),
            //     w(i)     := w(i+1), 
            //     w(i+1)   := 0,
            //     L(:,i)   += gamma L(:,i+1),
            //     U(i+1,:) -= gamma U(i,:).
            const F gamma = omega_i / omega_ip1;
            const F lambda_ii = F(1) + gamma*lambdaSub;
            A(i,  i) = gamma;
            A(i+1,i) = 0;

            auto lBiCopy = lBi;
            Swap( NORMAL, lBi, lBip1 );
            Axpy( gamma, lBiCopy, lBi );

            auto uip1RCopy = uip1R;
            RowSwap( A, i, i+1 );
            Axpy( -gamma, uip1RCopy, uip1R );

            // Force L back to *unit* lower-triangular form via the transform
            //     L := L T_{i,U}^{-1} D^{-1}, 
            // where D is diagonal and responsible for forcing L(i,i) and 
            // L(i+1,i+1) back to 1. The effect on L is:
            //     eta       := L(i,i+1)/L(i,i),
            //     L(:,i+1)  -= eta L(:,i),
            //     delta_i   := L(i,i),
            //     delta_ip1 := L(i+1,i+1),
            //     L(:,i)   /= delta_i,
            //     L(:,i+1) /= delta_ip1,
            // while the effect on U is
            //     U(i,:)   += eta U(i+1,:)
            //     U(i,:)   *= delta_i,
            //     U(i+1,:) *= delta_{i+1},
            // and the effect on w is
            //     w(i) *= delta_i.
            const F eta = lambdaSub/lambda_ii;
            const F delta_i = lambda_ii;
            const F delta_ip1 = F(1) - eta*gamma;

            Axpy( -eta, lBi, lBip1 );
            A(i+1,i) = gamma/delta_i;
            lBi   *= F(1)/delta_i;
            lBip1 *= F(1)/delta_ip1;

            A(i,i) = eta*ups_ii*delta_i;
            Axpy( eta, uip1R, uiR );
            uiR   *= delta_i;
            uip1R *= delta_ip1;
            uSub(i) = ups_ii*delta_ip1;

            // Finally set w(i)
            w(i) = omega_ip1*delta_i;
        }
        else
        {
            // Update
            //     L := L T_{i,L}^{-1},
            //     U := T_{i,L} U, 
            //     w := T_{i,L} w,
            // where T_{i,L} is the Gauss transform which zeros w_{i+1}.
            // 
            // More succinctly,
            //     gamma    := w(i+1) / w(i),
            //     L(:,i)   += gamma L(:,i+1),
            //     U(i+1,:) -= gamma U(i,:),
            //     w(i+1)   := 0.
            const F gamma = omega_ip1 / omega_i;
            A(i+1,i) += gamma;
            Axpy(  gamma, lBip1, lBi );
            Axpy( -gamma, uiR, uip1R );
            uSub(i) = -gamma*ups_ii;
        }
    }

    // Add the modified w v' into U
    {
        auto a0 = A( IR(0), ALL );
        const F omega_0 = w(0); 
        Matrix<F> vTrans;
        Transpose( v, vTrans, conjugate );
        Axpy( omega_0, vTrans, a0 );
    }

    // Transform U from upper-Hessenberg to upper-triangular form
    for( Int i=0; i<minDim-1; ++i ) 
    {
        // Decide if we should pivot the i'th and i+1'th rows U
        const F lambdaSub = A(i+1,i);
        const F ups_ii = A(i,i);
        const F ups_ip1i = uSub(i);
        const Real rightTerm = Abs(lambdaSub*ups_ii+ups_ip1i);
        const bool pivot = ( Abs(ups_ii) < tau*rightTerm );

        const Range<Int> indi( i, i+1 ),
                         indip1( i+1, i+2 ),
                         indB( i+2, m ),
                         indR( i+1, n );

        auto lBi   = A( indB,   indi   );
        auto lBip1 = A( indB,   indip1 );
        auto uiR   = A( indi,   indR   );
        auto uip1R = A( indip1, indR   );

        if( pivot )
        {
            // P := P_i P
            P.Swap( i, i+1 );

            // Simultaneously perform 
            //   U := P_i U and
            //   L := P_i L P_i^T
            //
            // Then update
            //     L := L T_{i,L}^{-1},
            //     U := T_{i,L} U, 
            // where T_{i,L} is the Gauss transform which zeros U(i+1,i).
            // 
            // More succinctly,
            //     gamma    := U(i+1,i) / U(i,i),
            //     L(:,i)   += gamma L(:,i+1),
            //     U(i+1,:) -= gamma U(i,:).
            const F gamma = ups_ii / ups_ip1i;
            const F lambda_ii = F(1) + gamma*lambdaSub;
            A(i+1,i) = ups_ip1i;
            A(i,  i) = gamma;

            auto lBiCopy = lBi;
            Swap( NORMAL, lBi, lBip1 );
            Axpy( gamma, lBiCopy, lBi );

            auto uip1RCopy = uip1R;
            RowSwap( A, i, i+1 );
            Axpy( -gamma, uip1RCopy, uip1R );

            // Force L back to *unit* lower-triangular form via the transform
            //     L := L T_{i,U}^{-1} D^{-1}, 
            // where D is diagonal and responsible for forcing L(i,i) and 
            // L(i+1,i+1) back to 1. The effect on L is:
            //     eta       := L(i,i+1)/L(i,i),
            //     L(:,i+1)  -= eta L(:,i),
            //     delta_i   := L(i,i),
            //     delta_ip1 := L(i+1,i+1),
            //     L(:,i)   /= delta_i,
            //     L(:,i+1) /= delta_ip1,
            // while the effect on U is
            //     U(i,:)   += eta U(i+1,:)
            //     U(i,:)   *= delta_i,
            //     U(i+1,:) *= delta_{i+1}.
            const F eta = lambdaSub/lambda_ii;
            const F delta_i = lambda_ii;
            const F delta_ip1 = F(1) - eta*gamma;

            Axpy( -eta, lBi, lBip1 );
            A(i+1,i) = gamma/delta_i;
            lBi   *= F(1)/delta_i;
            lBip1 *= F(1)/delta_ip1;

            A(i,i) = ups_ip1i*delta_i;
            Axpy( eta, uip1R, uiR );
            uiR   *= delta_i;
            uip1R *= delta_ip1;
        }
        else
        {
            // Update
            //     L := L T_{i,L}^{-1},
            //     U := T_{i,L} U, 
            // where T_{i,L} is the Gauss transform which zeros U(i+1,i).
            // 
            // More succinctly,
            //     gamma    := U(i+1,i)/ U(i,i),
            //     L(:,i)   += gamma L(:,i+1),
            //     U(i+1,:) -= gamma U(i,:).
            const F gamma = ups_ip1i / ups_ii;
            A(i+1,i) += gamma;
            Axpy(  gamma, lBip1, lBi );
            Axpy( -gamma, uiR, uip1R );
        }
    }
}