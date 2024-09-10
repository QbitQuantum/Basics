    void assemble_cortical(const Geometry& geo, Matrix& mat, const Head2EEGMat& M, const std::string& domain_name, const unsigned gauss_order, double alpha, double beta, const std::string &filename)
    {
        // Following the article: M. Clerc, J. Kybic "Cortical mapping by Laplace–Cauchy transmission using a boundary element method".
        // Assumptions:
        // - domain_name: the domain containing the sources is an innermost domain (defined as the interior of only one interface (called Cortex)
        // - Cortex interface is composed of one mesh only (no shared vertices)
        // TODO check orders of MxM products for efficiency ... delete intermediate matrices
        const Domain& SourceDomain = geo.domain(domain_name);
        const Interface& Cortex    = SourceDomain.begin()->interface();
        const Mesh& cortex         = Cortex.begin()->mesh();
        // test the assumption
        assert(SourceDomain.size() == 1);
        assert(Cortex.size() == 1);
        // shape of the new matrix:
        unsigned Nl = geo.size()-geo.outermost_interface().nb_triangles()-Cortex.nb_vertices()-Cortex.nb_triangles();
        unsigned Nc = geo.size()-geo.outermost_interface().nb_triangles();
        std::fstream f(filename.c_str());
        Matrix P;
        if ( !f ) {
            // build the HeadMat:
            // The following is the same as assemble_HM except N_11, D_11 and S_11 are not computed.
            SymMatrix mat_temp(Nc);
            mat_temp.set(0.0);
            double K = 1.0 / (4.0 * M_PI);
            // We iterate over the meshes (or pair of domains) to fill the lower half of the HeadMat (since its symmetry)
            for ( Geometry::const_iterator mit1 = geo.begin(); mit1 != geo.end(); ++mit1) {
                for ( Geometry::const_iterator mit2 = geo.begin(); (mit2 != (mit1+1)); ++mit2) {
                    // if mit1 and mit2 communicate, i.e they are used for the definition of a common domain
                    const int orientation = geo.oriented(*mit1, *mit2); // equals  0, if they don't have any domains in common
                    // equals  1, if they are both oriented toward the same domain
                    // equals -1, if they are not
                    if ( orientation != 0) {
                        double Scoeff =   orientation * geo.sigma_inv(*mit1, *mit2) * K;
                        double Dcoeff = - orientation * geo.indicator(*mit1, *mit2) * K;
                        double Ncoeff;
                        if ( !(mit1->outermost() || mit2->outermost()) && ( (*mit1 != *mit2)||( *mit1 != cortex) ) ) {
                            // Computing S block first because it's needed for the corresponding N block
                            operatorS(*mit1, *mit2, mat_temp, Scoeff, gauss_order);
                            Ncoeff = geo.sigma(*mit1, *mit2)/geo.sigma_inv(*mit1, *mit2);
                        } else {
                            Ncoeff = orientation * geo.sigma(*mit1, *mit2) * K;
                        }
                        if ( !mit1->outermost() && (( (*mit1 != *mit2)||( *mit1 != cortex) )) ) {
                            // Computing D block
                            operatorD(*mit1, *mit2, mat_temp, Dcoeff, gauss_order);
                        }
                        if ( ( *mit1 != *mit2 ) && ( !mit2->outermost() ) ) {
                            // Computing D* block
                            operatorD(*mit1, *mit2, mat_temp, Dcoeff, gauss_order, true);
                        }
                        // Computing N block
                        if ( (*mit1 != *mit2)||( *mit1 != cortex) ) {
                            operatorN(*mit1, *mit2, mat_temp, Ncoeff, gauss_order);
                        }
                    }
                }
            }
            // Deflate the diagonal block (N33) of 'mat' : (in order to have a zero-mean potential for the outermost interface)
            const Interface i = geo.outermost_interface();
            unsigned i_first = (*i.begin()->mesh().vertex_begin())->index();
            deflat(mat_temp, i, mat_temp(i_first, i_first) / (geo.outermost_interface().nb_vertices()));

            mat = Matrix(Nl, Nc);
            mat.set(0.0);
            // copy mat_temp into mat except the lines for cortex vertices [i_vb_c, i_ve_c] and cortex triangles [i_tb_c, i_te_c].
            unsigned iNl = 0;
            unsigned i_vb_c = (*cortex.vertex_begin())->index();
            unsigned i_ve_c = (*cortex.vertex_rbegin())->index();
            unsigned i_tb_c = cortex.begin()->index();
            unsigned i_te_c = cortex.rbegin()->index();
            for ( unsigned i = 0; i < Nc; ++i) {
                if ( !(i_vb_c<=i && i<=i_ve_c) && !(i_tb_c<=i && i<=i_te_c) ) {
                    mat.setlin(iNl, mat_temp.getlin(i));
                    ++iNl;
                }
            }
            // ** Construct P: the null-space projector **
            Matrix W;
            {
                Matrix U, s;
                mat.svd(U, s, W);
            }

            SparseMatrix S(Nc,Nc);
            // we set S to 0 everywhere, except in the last part of the diag:
            for ( unsigned i = Nl; i < Nc; ++i) {
                S(i, i) = 1.0;
            }
            P = (W * S) * W.transpose(); // P is a projector: P^2 = P and mat*P*X = 0
            if ( filename.length() != 0 ) {
                std::cout << "Saving projector P (" << filename << ")." << std::endl;
                P.save(filename);
            }
        } else {
            std::cout << "Loading projector P (" << filename << ")." << std::endl;
            P.load(filename);
        }

        // ** Get the gradient of P1&P0 elements on the meshes **
        Matrix MM(M.transpose() * M);
        SymMatrix RR(Nc, Nc); RR.set(0.);
        for ( Geometry::const_iterator mit = geo.begin(); mit != geo.end(); ++mit) {
            mit->gradient_norm2(RR);
        }

        // ** Choose Regularization parameter **
        SparseMatrix alphas(Nc,Nc); // diagonal matrix
        Matrix Z;
        if ( alpha < 0 ) { // try an automatic method... TODO find better estimation
            double nRR_v = RR.submat(0, geo.nb_vertices(), 0, geo.nb_vertices()).frobenius_norm();
            alphas.set(0.);
            alpha = MM.frobenius_norm() / (1.e3*nRR_v);
            beta  = alpha * 50000.;
            for ( Vertices::const_iterator vit = geo.vertex_begin(); vit != geo.vertex_end(); ++vit) {
                alphas(vit->index(), vit->index()) = alpha;
            }
            for ( Meshes::const_iterator mit = geo.begin(); mit != geo.end(); ++mit) {
                if ( !mit->outermost() ) {
                    for ( Mesh::const_iterator tit = mit->begin(); tit != mit->end(); ++tit) {
                        alphas(tit->index(), tit->index()) = beta;
                    }
                }
            }
            std::cout << "AUTOMATIC alphas = " << alpha << "\tbeta = " << beta << std::endl;
        } else {
            for ( Vertices::const_iterator vit = geo.vertex_begin(); vit != geo.vertex_end(); ++vit) {
                alphas(vit->index(), vit->index()) = alpha;
            }
            for ( Meshes::const_iterator mit = geo.begin(); mit != geo.end(); ++mit) {
                if ( !mit->outermost() ) {
                    for ( Mesh::const_iterator tit = mit->begin(); tit != mit->end(); ++tit) {
                        alphas(tit->index(), tit->index()) = beta;
                    }
                }
            }
            std::cout << "alphas = " << alpha << "\tbeta = " << beta << std::endl;
        }
        Z = P.transpose() * (MM + alphas*RR) * P;

        // ** PseudoInverse and return **
        // X = P * { (M*P)' * (M*P) + (R*P)' * (R*P) }¡(-1) * (M*P)'m
        // X = P * { P'*M'*M*P + P'*R'*R*P }¡(-1) * P'*M'm
        // X = P * { P'*(MM + a*RR)*P }¡(-1) * P'*M'm
        // X = P * Z¡(-1) * P' * M'm
        Matrix rhs = P.transpose() * M.transpose();
        mat = P * Z.pinverse() * rhs;
    }