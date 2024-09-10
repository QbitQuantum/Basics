void CKroneckerLMM::updateDecomposition()  {
    //check that dimensions match
    this->num_samples = snps.rows();
    this->num_snps = snps.cols();
    this->num_pheno = pheno.cols();
    //this->num_covs = covs.cols();

    if (num_samples==0)
        throw CLimixException("LMM requires a non-zero sample size");

    if (num_snps==0)
        throw CLimixException("LMM requires non-zero SNPs");

    if (num_pheno==0)
        throw CLimixException("LMM requires non-zero phenotypes");

    if(!(num_samples == (muint_t) pheno.rows()) || !(num_samples == (muint_t) snps.rows()) )
        throw CLimixException("phenotypes and SNP dimensions inconsistent");

    //if(!num_samples == covs.rows())
    //    throw CLimixException("covariates and SNP dimensions inconsistent");

    //decomposition of K//should be a Cholesky for speed
	Eigen::SelfAdjointEigenSolver<MatrixXd> eigensolver2c(K2c);
    this->U2c = eigensolver2c.eigenvectors();
    this->S2c = eigensolver2c.eigenvalues();
	if (!(this->S2c(0)>1e-12)){
		throw CLimixException("The column covariance of the second covariance term has to be full rank, but is not.");
	}

	Eigen::SelfAdjointEigenSolver<MatrixXd> eigensolver2r(K2r);
    this->U2r = eigensolver2r.eigenvectors();
    this->S2r = eigensolver2r.eigenvalues();
	if (!(this->S2r(0)>1e-12)){
		throw CLimixException("The row covariance of the second covariance term has to be full rank, but is not.");
	}
        
	this->Rrot = this->U2r;
	this->Crot = this->U2c;
#ifdef debugkron
	std::cout << "Crot: \n"<< Crot << "\n";
	std::cout << "Rrot: \n"<< Rrot << "\n";
#endif		
	for (size_t r1=0;r1<(muint_t)this->pheno.rows();++r1)
	{
		for (size_t r2=0;r2<(muint_t)this->pheno.rows();++r2)
		{
			Rrot(r1,r2)/=sqrt(this->S2r(r2));
		}
	}
	for (size_t c1=0;c1<(muint_t)this->pheno.cols();++c1)
	{
		for (size_t c2=0;c2<(muint_t)this->pheno.cols();++c2)
		{
			Crot(c1,c2)/=sqrt(this->S2c(c2));
		}
	}
#ifdef debugkron
	std::cout << "Crot: \n"<< Crot << "\n";
	std::cout << "Rrot: \n"<< Rrot << "\n";
#endif
	MatrixXd S2U2K1r = this->Rrot.transpose() * this->K1r * this->Rrot;
	MatrixXd S2U2K1c = this->Crot.transpose() * this->K1c * this->Crot;
		

	Eigen::SelfAdjointEigenSolver<MatrixXd> eigensolver1c(S2U2K1c);
    this->U1c = eigensolver1c.eigenvectors();
    this->S1c = eigensolver1c.eigenvalues();

	Eigen::SelfAdjointEigenSolver<MatrixXd> eigensolver1r(S2U2K1r);
    this->U1r = eigensolver1r.eigenvectors();
    this->S1r = eigensolver1r.eigenvalues();
#ifdef debugkron
	MatrixXd K2ri_ = Rrot * Rrot.transpose(); 
	MatrixXd K2ci_ = Crot * Crot.transpose(); 
	std::cout << "K2ri_: \n"<<  K2ri_ << "\n";
	std::cout << "K2ci_: \n"<<  K2ci_ << "\n";
	std::cout << "K2ri : \n"<<  K2r.inverse() << "\n";
	std::cout << "K2ci : \n"<<  K2c.inverse() << "\n";
#endif
	Rrot *= this->U1r;//multiply from right with U1r
	Crot *= this->U1c;//multiply from right with U1c

#ifdef debugkron
	MatrixXd K2ri =   Rrot * Rrot.transpose(); 
	MatrixXd K2ci =   Crot * Crot.transpose(); 
	std::cout << "K2ri_: \n"<<  K2ri << "\n";
	std::cout << "K2ci_: \n"<<  K2ci << "\n";
	std::cout << "K2ri : \n"<<  K2r.inverse() << "\n";
	std::cout << "K2ci : \n"<<  K2c.inverse() << "\n";
		
	mfloat_t delta = 0.01;
		
	MatrixXd kronK1;
	akron(kronK1,K1c,K1r,false);
	std::cout << "K1r: \n"<<  K1r << "\n";
	std::cout << "K1c: \n"<<  K1c << "\n";
	std::cout << "K2r: \n"<<  K2r << "\n";
	std::cout << "K2c: \n"<<  K2c << "\n";
		
	MatrixXd kronK2;
	akron(kronK2,K2c,K2r,false);
	MatrixXd kronK = kronK1+delta*kronK2;
	std::cout << "kronK1: \n"<<  kronK1 << "\n";
	std::cout << "kronK2: \n"<<  kronK2 << "\n";
		
	MatrixXd kronKi = kronK.inverse();
		
	akron(kronK1,Crot,Rrot,false);
	std::cout << "Crot: \n"<< Crot << "\n";
	std::cout << "Rrot: \n"<< Rrot << "\n";
	for (size_t c1=0;c1<this->pheno.cols();++c1)
	{
		for (size_t c2=0;c2<this->pheno.cols();++c2)
		{
			for (size_t r1=0;r1<this->pheno.rows();++r1)
			{
				for (size_t r2=0;r2<this->pheno.rows();++r2)
				{
					mfloat_t S = this->S1c(c2)*this->S1r(r2) + delta;
					kronK1(c1*this->pheno.rows()+r1,c2*this->pheno.rows()+r2)/=sqrt(S);
				}
			}
		}
	}

	MatrixXd kronKi_ = kronK1*kronK1.transpose();
	std::cout << "Ki_: \n"<< kronKi_ << "\n";
	std::cout << "Ki : \n"<< kronKi << "\n";
	mfloat_t diff = (kronKi-kronKi_).norm();
	std::cout << "diff: "<< diff << "\n";
	
	mfloat_t logdet = log(kronK.determinant());
	mfloat_t logdet_ = 0.0;
	for (size_t r1=0;r1<this->pheno.rows();++r1)
	{
		logdet_+=pheno.cols()*log(this->S2r(r1));
	}
	for (size_t c1=0;c1<this->pheno.cols();++c1)
	{
		logdet_+=pheno.rows()*log(this->S2c(c1));
	}
	for (size_t c1=0;c1<this->pheno.cols();++c1)
	{
		for (size_t r1=0;r1<this->pheno.rows();++r1)
		{
			logdet_+=log(this->S1c(c1)*this->S1r(r1) + delta);
		}
	} 
	std::cout << "logdet :" << logdet<<"\n";
	std::cout << "logdet_:" << logdet_<<"\n";
	std::cout << "diff:" << logdet_-logdet<<"\n";

#endif

	//snps
    Usnps.noalias() = this->Rrot.transpose() * snps;

	//SNP column design matrix
	//design for SNPs
	this->snpcoldesignU.noalias() = snpcoldesign * this->Crot;
	if (this->snpcoldesign0_inter.rows()!=0) //check if interaction design matrix is set
	{
		this->snpcoldesignU0_inter.noalias() = snpcoldesign0_inter * this->Crot;
	}

	//phenotype
	Upheno.noalias() = this->Rrot.transpose() * pheno * this->Crot;

	//need column design matrix
	//rotate covariates
	this->Urowdesign0=MatrixXdVec();
	this->coldesignU0=MatrixXdVec();
	for(muint_t term = 0; term<coldesign0.size();++term)
	{
		Urowdesign0.push_back(Rrot.transpose() * rowdesign0[term]);
		coldesignU0.push_back(coldesign0[term] * Crot);
	}//end loop over covariates terms		
}