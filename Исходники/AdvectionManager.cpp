void AdvectionManager::advance(double dt, const TimeLevelIndex<2> &newTimeIdx,
                               const VelocityField &velocity) {
    TimeLevelIndex<2> oldTimeIdx = newTimeIdx-1;
    TimeLevelIndex<2> halfTimeIdx = newTimeIdx-0.5;
    const double eps = 1.0e-80;
    const double R = domain->getRadius();
    for (int s = 0; s < Q.size(); ++s) {
        ScalarField &q = *Q[s];
        double dQ;
        int J;
//#define ONLY_LAX_WENDROFF
//#define ONLY_UPWIND
#ifndef ONLY_UPWIND
        // ---------------------------------------------------------------------
        // Lax-Wendroff pass
        for (int j = 1; j < mesh->getNumGrid(1, FULL)-1; ++j) {
            for (int i = 0; i < mesh->getNumGrid(0, HALF); ++i) {
                double f1 = dt/(R*dlon[i]);
                double f2 = f1/cosLatFull[j];
                double u = velocity(0)(halfTimeIdx, i, j);
                double q1 = q(oldTimeIdx, i,   j);
                double q2 = q(oldTimeIdx, i+1, j);
                FX(i, j) = 0.5*f1*(u*(q2+q1)-u*u*f2*(q2-q1));
            }
        }
        FX.applyBndCond();
        for (int j = 0; j < mesh->getNumGrid(1, HALF); ++j) {
            for (int i = 0; i < mesh->getNumGrid(0, FULL); ++i) {
                double f1 = dt/(R*dlat[j]);
                double f2 = f1/cosLatHalf[j];
                double v = velocity(1)(halfTimeIdx, i, j)*cosLatHalf[j];
                double q1 = q(oldTimeIdx, i, j  );
                double q2 = q(oldTimeIdx, i, j+1);
                FY(i, j) = 0.5*f1*(v*(q2+q1)-v*v*f2*(q2-q1));
            }
        }
        FY.applyBndCond();
#endif
#if (!defined ONLY_LAX_WENDROFF && !defined ONLY_UPWIND)
        // ---------------------------------------------------------------------
        // calculate intermediate Qstar
        for (int j = 1; j < mesh->getNumGrid(1, FULL)-1; ++j) {
            for (int i = 0; i < mesh->getNumGrid(0, FULL); ++i) {
                double fx1 = dt/(R*dlon[i]*cosLatFull[i]); // TODO: Should we support irregular lon grids?
                double fx2 = dt/(R*dlon[i]*cosLatFull[i]);
                double fy1 = dt/(R*dlat[j-1]*cosLatHalf[j-1]);
                double fy2 = dt/(R*dlat[j  ]*cosLatHalf[j  ]);
                double u1 = velocity(0)(halfTimeIdx, i-1, j);
                double u2 = velocity(0)(halfTimeIdx, i,   j);
                double v1 = velocity(1)(halfTimeIdx, i, j-1);
                double v2 = velocity(1)(halfTimeIdx, i, j  );
                double tmp1 = fabs(u1*fx1)*(1-fabs(u1*fx1));
                double tmp2 = fabs(u2*fx2)*(1-fabs(u2*fx2));
                double tmp3 = fabs(v1*fy1)*(1-fabs(v1*fy1));
                double tmp4 = fabs(v2*fy2)*(1-fabs(v2*fy2));
                double gamma = fmax(fmax(tmp1, tmp2), fmax(tmp3, tmp4));
                B(i, j) = 2/(2-2*gamma);
            }
        }
        for (int j = 1; j < mesh->getNumGrid(1, FULL)-1; ++j) {
            for (int i = 0; i < mesh->getNumGrid(0, FULL); ++i) {
                Qstar(i, j) = q(oldTimeIdx, i, j)-B(i, j)/cosLatFull[j]*
                    (FX(i, j)-FX(i-1, j)+FY(i, j)-FY(i, j-1));
            }
        }
        // handle poles
        // south pole
        dQ = 0; J = 0;
        for (int i = 0; i < mesh->getNumGrid(0, FULL); ++i) {
            dQ += B(i, J+1)*FY(i, J);
        }
        dQ *= 4.0/mesh->getNumGrid(0, FULL)/cosLatHalf[J];
        for (int i = 0; i < mesh->getNumGrid(0, FULL); ++i) {
            Qstar(i, J) = q(oldTimeIdx, i, J)-dQ;
        }
        // north pole
        dQ = 0; J = mesh->getNumGrid(1, FULL)-1;
        for (int i = 0; i < mesh->getNumGrid(0, FULL); ++i) {
            dQ += B(i, J-1)*FY(i, J-1);
        }
        dQ *= 4.0/mesh->getNumGrid(0, FULL)/cosLatHalf[J-1];
        for (int i = 0; i < mesh->getNumGrid(0, FULL); ++i) {
            Qstar(i, J) = q(oldTimeIdx, i, J)+dQ;
        }
        // ---------------------------------------------------------------------
        // shape-preserving rule (A <= 0 is good)
        for (int j = 0; j < mesh->getNumGrid(1, FULL); ++j) {
            for (int i = 0; i < mesh->getNumGrid(0, FULL); ++i) {
                double Qmin =  1.0e+15;
                double Qmax = -1.0e+15;
                if (j == 0) {
                    Qmin = fmin(fmin(q(oldTimeIdx, i, j), q(oldTimeIdx, i, j+1)), Qmin);
                    Qmax = fmax(fmax(q(oldTimeIdx, i, j), q(oldTimeIdx, i, j+1)), Qmax);
                } else if (j == mesh->getNumGrid(1, FULL)-1) {
                    Qmin = fmin(fmin(q(oldTimeIdx, i, j), q(oldTimeIdx, i, j-1)), Qmin);
                    Qmax = fmax(fmax(q(oldTimeIdx, i, j), q(oldTimeIdx, i, j-1)), Qmax);
                } else {
                    Qmin = fmin(fmin(fmin(q(oldTimeIdx, i-1, j), q(oldTimeIdx, i+1, j)),
                                     fmin(q(oldTimeIdx, i, j-1), q(oldTimeIdx, i, j+1))),
                                fmin(q(oldTimeIdx, i, j), Qmin));
                    Qmax = fmax(fmax(fmax(q(oldTimeIdx, i-1, j), q(oldTimeIdx, i+1, j)),
                                     fmax(q(oldTimeIdx, i, j-1), q(oldTimeIdx, i, j+1))),
                                fmax(q(oldTimeIdx, i, j), Qmax));
                }
                A(i, j) = (Qstar(i, j)-Qmax)*(Qstar(i, j)-Qmin);
            }
        }
        A.applyBndCond();
#endif
#ifndef ONLY_LAX_WENDROFF
        // ---------------------------------------------------------------------
        // upwind pass
        for (int j = 1; j < mesh->getNumGrid(1, FULL)-1; ++j) {
            for (int i = 0; i < mesh->getNumGrid(0, HALF); ++i) {
#ifndef ONLY_UPWIND
                double tmp1 = (fabs(A(i,   j))+A(i,   j))/(fabs(A(i,   j))+eps);
                double tmp2 = (fabs(A(i+1, j))+A(i+1, j))/(fabs(A(i+1, j))+eps);
                double tmp3 = (fabs(A(i+1, j))+A(i+1, j))*(fabs(A(i, j))+A(i, j));
                double tmp4 = fabs(A(i, j))*fabs(A(i+1, j))+eps;
                double cxstar = 0.5*(tmp1+tmp2)-0.25*tmp3/tmp4;
#else
                double cxstar = 1;
#endif
                double f = dt/(R*dlon[i]);
                double u = velocity(0)(halfTimeIdx, i, j);
                double q1 = q(oldTimeIdx, i,   j);
                double q2 = q(oldTimeIdx, i+1, j);
                double cx = cxstar+(1-cxstar)*fabs(u*f/cosLatFull[j]);
                FX(i, j) = 0.5*f*(u*(q2+q1)-fabs(cx*u)*(q2-q1));
            }
        }
        FX.applyBndCond();
        for (int j = 0; j < mesh->getNumGrid(1, HALF); ++j) {
            for (int i = 0; i < mesh->getNumGrid(0, FULL); ++i) {
#ifndef ONLY_UPWIND
                double tmp1 = (fabs(A(i, j  ))+A(i, j  ))/(fabs(A(i, j  ))+eps);
                double tmp2 = (fabs(A(i, j+1))+A(i, j+1))/(fabs(A(i, j+1))+eps);
                double tmp3 = (fabs(A(i, j+1))+A(i, j+1))*(fabs(A(i, j))+A(i, j));
                double tmp4 = fabs(A(i, j))*fabs(A(i, j+1))+eps;
                double cystar = 0.5*(tmp1+tmp2)-0.25*tmp3/tmp4;
#else
                double cystar = 1;
#endif
                double f = dt/(R*dlat[j]);
                double v = velocity(1)(halfTimeIdx, i, j)*cosLatHalf[j];
                double q1 = q(oldTimeIdx, i, j  );
                double q2 = q(oldTimeIdx, i, j+1);
                double cy = cystar+(1-cystar)*fabs(v*f/cosLatHalf[j]);
                FY(i, j) = 0.5*f*(v*(q2+q1)-fabs(cy*v)*(q2-q1));
            }
        }
        FY.applyBndCond();
#endif
        // ---------------------------------------------------------------------
        // calculate final Q
        for (int j = 1; j < mesh->getNumGrid(1, FULL)-1; ++j) {
            for (int i = 0; i < mesh->getNumGrid(0, FULL); ++i) {
                q(newTimeIdx, i, j) = q(oldTimeIdx, i, j)-
                    (FX(i, j)-FX(i-1, j)+FY(i, j)-FY(i, j-1))/cosLatFull[j];
            }
        }
        // handle poles
        // south pole
        dQ = 0; J = 0;
        for (int i = 0; i < mesh->getNumGrid(0, FULL); ++i) {
            dQ += FY(i, J);
        }
        dQ *= 4.0/mesh->getNumGrid(0, FULL)/cosLatHalf[J];
        for (int i = 0; i < mesh->getNumGrid(0, FULL); ++i) {
            q(newTimeIdx, i, J) = q(oldTimeIdx, i, J)-dQ;
        }
        // north pole
        dQ = 0; J = mesh->getNumGrid(1, FULL)-1;
        for (int i = 0; i < mesh->getNumGrid(0, FULL); ++i) {
            dQ += FY(i, J-1);
        }
        dQ *= 4.0/mesh->getNumGrid(0, FULL)/cosLatHalf[J-1];
        for (int i = 0; i < mesh->getNumGrid(0, FULL); ++i) {
            q(newTimeIdx, i, J) = q(oldTimeIdx, i, J)+dQ;
        }
        q.applyBndCond(newTimeIdx);
    }

    diagnose(newTimeIdx);
}