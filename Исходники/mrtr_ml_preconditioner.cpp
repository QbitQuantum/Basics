/*----------------------------------------------------------------------*
 |  compute the preconditioner (public)                      m.gee 03/06|
 *----------------------------------------------------------------------*/
bool MOERTEL::Mortar_ML_Preconditioner::Compute()
{

    iscomputed_ = false;

    MLAPI::Init();

    // get parameters
    int     maxlevels     = mlparams_.get("max levels",10);
    int     maxcoarsesize = mlparams_.get("coarse: max size",10);
    double* nullspace     = mlparams_.get("null space: vectors",(double*)NULL);
    int     nsdim         = mlparams_.get("null space: dimension",1);
    int     numpde        = mlparams_.get("PDE equations",1);
    double  damping       = mlparams_.get("aggregation: damping factor",1.33);
    std::string  eigenanalysis = mlparams_.get("eigen-analysis: type", "Anorm");
    std::string  smoothertype  = mlparams_.get("smoother: type","symmetric Gauss-Seidel");
    std::string  coarsetype    = mlparams_.get("coarse: type","Amesos-KLU");
    std::string  ptype         = mlparams_.get("prolongator: type","mod_full");

    // create the missing rowmap Arrmap_
    Arrmap_ = Teuchos::rcp(MOERTEL::SplitMap(A_->RowMap(),*Annmap_));
    Teuchos::RCP<Epetra_Map> map1 = Arrmap_;
    Teuchos::RCP<Epetra_Map> map2 = Annmap_;

    // split Atilde
    //
    //  Atilde11 Atilde12
    //  Atilde21 Atilde22
    //
    Teuchos::RCP<Epetra_CrsMatrix> Atilde11;
    Teuchos::RCP<Epetra_CrsMatrix> Atilde12;
    Teuchos::RCP<Epetra_CrsMatrix> Atilde21;
    Teuchos::RCP<Epetra_CrsMatrix> Atilde22;
    MOERTEL::SplitMatrix2x2(Atilde_,map1,map2,Atilde11,Atilde12,Atilde21,Atilde22);

    // build Atildesplit
    //
    //  Atilde11  0
    //  0         I
    //
    Atildesplit_ = Teuchos::rcp(new Epetra_CrsMatrix(Copy,A_->RowMap(),50,false));
    MOERTEL::MatrixMatrixAdd(*Atilde11,false,1.0,*Atildesplit_,0.0);
    Teuchos::RCP<Epetra_CrsMatrix> tmp = Teuchos::rcp(MOERTEL::PaddedMatrix(*map2,1.0,1));
    tmp->FillComplete();
    MOERTEL::MatrixMatrixAdd(*tmp,false,1.0,*Atildesplit_,1.0);
    Atildesplit_->FillComplete();
    Atildesplit_->OptimizeStorage();

    // split A
    //
    //  A11 A12
    //  A21 A22
    //
    Teuchos::RCP<Epetra_CrsMatrix> A11;
    Teuchos::RCP<Epetra_CrsMatrix> A12;
    Teuchos::RCP<Epetra_CrsMatrix> A21;
    Teuchos::RCP<Epetra_CrsMatrix> A22;
    MOERTEL::SplitMatrix2x2(A_,map1,map2,A11,A12,A21,A22);

    // build Asplit_
    //
    //  A11  0
    //  0    A22
    //
    Asplit_ = Teuchos::rcp(new Epetra_CrsMatrix(Copy,A_->RowMap(),50,false));
    MOERTEL::MatrixMatrixAdd(*A11,false,1.0,*Asplit_,0.0);
    MOERTEL::MatrixMatrixAdd(*A22,false,1.0,*Asplit_,1.0);
    Asplit_->FillComplete();
    Asplit_->OptimizeStorage();

    // build BWT (padded to full size)
    //
    //  0   Mr Dinv
    //  0    I
    //
    Teuchos::RCP<Epetra_CrsMatrix> BWT = Teuchos::rcp(MOERTEL::MatMatMult(*B_,false,*WT_,false,10));
    tmp = Teuchos::rcp(MOERTEL::PaddedMatrix(BWT->RowMap(),0.0,25));
    MOERTEL::MatrixMatrixAdd(*BWT,false,1.0,*tmp,0.0);
    tmp->FillComplete(BWT->DomainMap(),BWT->RangeMap());
    BWT = tmp;
    tmp = Teuchos::null;

    // split BWT to obtain M = Mr Dinv
    Teuchos::RCP<Epetra_CrsMatrix> Zero11;
    Teuchos::RCP<Epetra_CrsMatrix> M;
    Teuchos::RCP<Epetra_CrsMatrix> Zero21;
    Teuchos::RCP<Epetra_CrsMatrix> I22;
    MOERTEL::SplitMatrix2x2(BWT,map1,map2,Zero11,M,Zero21,I22);


    // build matrix Ahat11 = Atilde11 - M Atilde22 M^T
    Teuchos::RCP<Epetra_CrsMatrix> Ahat11 = Teuchos::rcp(new Epetra_CrsMatrix(Copy,*map1,50,false));
    MOERTEL::MatrixMatrixAdd(*Atilde11,false,1.0,*Ahat11,0.0);
    Teuchos::RCP<Epetra_CrsMatrix> tmp1 = Teuchos::rcp(MOERTEL::MatMatMult(*Atilde22,false,*M,true,10));
    Teuchos::RCP<Epetra_CrsMatrix> tmp2 = Teuchos::rcp(MOERTEL::MatMatMult(*M,false,*tmp1,false,10));
    MOERTEL::MatrixMatrixAdd(*tmp2,false,-1.0,*Ahat11,1.0);
    Ahat11->FillComplete();
    Ahat11->OptimizeStorage();

    // build matrix Ahat
    //
    //  Ahat11   0   =   Atilde11 - M Atilde22 M^T   0
    //  0        0       0                           0
    //
    Ahat_ = Teuchos::rcp(MOERTEL::PaddedMatrix(A_->RowMap(),0.0,25));
    MOERTEL::MatrixMatrixAdd(*Ahat11,false,1.0,*Ahat_,0.0);
    Ahat_->FillComplete();
    Ahat_->OptimizeStorage();


    // build mlapi objects
    Space space(A_->RowMatrixRowMap());
    Operator mlapiAsplit(space,space,Asplit_.get(),false);
    Operator mlapiAtildesplit(space,space,Atildesplit_.get(),false);
    Operator mlapiAhat(space,space,Ahat_.get(),false);
    Operator mlapiBWT(space,space,BWT.get(),false);
    Operator mlapiBWTcoarse;
    Operator ImBWTfine = GetIdentity(space,space) - mlapiBWT;
    Operator ImBWTcoarse;
    Operator Ptent;
    Operator P;
    Operator Pmod;
    Operator Rtent;
    Operator R;
    Operator Rmod;
    Operator IminusA;
    Operator C;
    InverseOperator S;

    mlapiAtildesplit_.resize(maxlevels);
    mlapiAhat_.resize(maxlevels);
    mlapiImBWT_.resize(maxlevels);
    mlapiImWBT_.resize(maxlevels);
    mlapiRmod_.resize(maxlevels);
    mlapiPmod_.resize(maxlevels);
    mlapiS_.resize(maxlevels);

    mlapiAtildesplit_[0] = mlapiAtildesplit;
    mlapiAhat_[0]        = mlapiAhat;
    mlapiImBWT_[0]       = ImBWTfine;
    mlapiImWBT_[0]       = GetTranspose(ImBWTfine);


    // build nullspace
    MultiVector NS;
    MultiVector NextNS;
    NS.Reshape(mlapiAsplit.GetRangeSpace(),nsdim);
    if (nullspace)
    {
        for (int i=0; i<nsdim; ++i)
            for (int j=0; j<NS.GetMyLength(); ++j)
                NS(j,i) = nullspace[i*NS.GetMyLength()+j];
    }
    else
    {
        if (numpde==1) NS = 1.0;
        else
        {
            NS = 0.0;
            for (int i=0; i<NS.GetMyLength(); ++i)
                for (int j=0; j<numpde; ++j)
                    if ( i % numpde == j)
                        NS(i,j) = 1.0;
        }
    }

    double lambdamax;

    // construct the hierarchy
    int level=0;
    for (level=0; level<maxlevels-1; ++level)
    {
        // this level's smoothing operator
        mlapiAtildesplit = mlapiAtildesplit_[level];

        // build smoother
        if (Comm().MyPID()==0)
        {
            ML_print_line("-", 78);
            std::cout << "MOERTEL/ML : creating smoother level " << level << std::endl;
            fflush(stdout);
        }
        S.Reshape(mlapiAtildesplit,smoothertype,mlparams_);

        if (level) mlparams_.set("PDE equations", NS.GetNumVectors());

        if (Comm().MyPID()==0)
        {
            ML_print_line("-", 80);
            std::cout << "MOERTEL/ML : creating level " << level+1 << std::endl;
            ML_print_line("-", 80);
            fflush(stdout);
        }
        mlparams_.set("workspace: current level",level);

        // get tentative prolongator based on decoupled original system
        GetPtent(mlapiAsplit,mlparams_,NS,Ptent,NextNS);
        NS = NextNS;

        // do prolongator smoothing
        if (damping)
        {
            if (eigenanalysis == "Anorm")
                lambdamax = MaxEigAnorm(mlapiAsplit,true);
            else if (eigenanalysis == "cg")
                lambdamax = MaxEigCG(mlapiAsplit,true);
            else if (eigenanalysis == "power-method")
                lambdamax = MaxEigPowerMethod(mlapiAsplit,true);
            else ML_THROW("incorrect parameter (" + eigenanalysis + ")", -1);

            IminusA = GetJacobiIterationOperator(mlapiAsplit,damping/lambdamax);
            P       = IminusA * Ptent;
            R       = GetTranspose(P);
            Rtent   = GetTranspose(Ptent);
        }
        else
        {
            P     = Ptent;
            Rtent = GetTranspose(Ptent);
            R     = Rtent;
            lambdamax = -1.0;
        }

        // do variational coarse grid of split original matrix Asplit
        C = GetRAP(R,mlapiAsplit,P);

        // compute the mortar projections on coarse grid
        mlapiBWTcoarse = GetRAP(Rtent,mlapiBWT,Ptent);
        ImBWTcoarse    = GetIdentity(C.GetDomainSpace(),C.GetRangeSpace());
        ImBWTcoarse    = ImBWTcoarse - mlapiBWTcoarse;

        // do modified prolongation and restriction
        if (ptype=="mod_full")
            Rmod = ImBWTcoarse * ( R * ImBWTfine ) + mlapiBWTcoarse * ( R * mlapiBWT );
        else if (ptype=="mod_middle")
            Rmod = ImBWTcoarse * ( R * ImBWTfine );
        else if (ptype=="mod_simple")
            Rmod = R * ImBWTfine;
        else if (ptype=="original")
            Rmod = R;
        else
            ML_THROW("incorrect parameter ( " + ptype + " )", -1);
        Pmod = GetTranspose(Rmod);

        // store matrix for construction of next level
        mlapiAsplit = C;

        // make coarse smoothing operator
        // make coarse residual operator
        mlapiAtildesplit_[level+1] = GetRAP(Rmod,mlapiAtildesplit,Pmod);
        mlapiAhat_[level+1]        = GetRAP(Rmod,mlapiAhat_[level],Pmod);
        mlapiImBWT_[level]         = ImBWTfine;
        mlapiImBWT_[level+1]       = ImBWTcoarse;
        mlapiImWBT_[level]         = GetTranspose(ImBWTfine);
        mlapiImWBT_[level+1]       = GetTranspose(ImBWTcoarse);
        mlapiRmod_[level]          = Rmod;
        mlapiPmod_[level]          = Pmod;
        mlapiS_[level]             = S;

        // prepare for next level
        mlapiBWT  = mlapiBWTcoarse;
        ImBWTfine = ImBWTcoarse;

        // break if coarsest level is below specified size
        if (mlapiAsplit.GetNumGlobalRows() <= maxcoarsesize)
        {
            ++level;
            break;
        }

    } // for (level=0; level<maxlevels-1; ++level)

    // do coarse smoother
    S.Reshape(mlapiAtildesplit_[level],coarsetype,mlparams_);
    mlapiS_[level] = S;

    // store max number of levels
    maxlevels_ = level+1;

    iscomputed_ = true;
    return true;
}