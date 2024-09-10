void GradientDataExport<dim>::eval_and_deriv(MathVector<dim> vValue[],
                    const MathVector<dim> vGlobIP[],
                    number time, int si,
                    GridObject* elem,
                    const MathVector<dim> vCornerCoords[],
                    const MathVector<refDim> vLocIP[],
                    const size_t nip,
                    LocalVector* u,
                    bool bDeriv,
                    int s,
                    std::vector<std::vector<MathVector<dim> > > vvvDeriv[],
                    const MathMatrix<refDim, dim>* vJT) const
{
//	abbreviation for component
	static const int _C_ = 0;

//	reference object id
	const ReferenceObjectID roid = elem->reference_object_id();

//	local finite element id
	const LFEID& lfeID = this->function_group().local_finite_element_id(_C_);

//	access local vector by map
	u->access_by_map(this->map());

//	request for trial space
	try{
	const LocalShapeFunctionSet<refDim>& rTrialSpace
		 = LocalFiniteElementProvider::get<refDim>(roid, lfeID);

//	Reference Mapping
	MathMatrix<dim, refDim> JTInv;
	std::vector<MathMatrix<refDim, dim> > vJTtmp;
	if(!vJT){
		DimReferenceMapping<refDim, dim>& map
			= ReferenceMappingProvider::get<refDim, dim>(roid, vCornerCoords);

		vJTtmp.resize(nip);
		map.jacobian_transposed(&vJTtmp[0], vLocIP, nip);
		vJT = &vJTtmp[0];
	}

//	storage for shape function at ip
	std::vector<MathVector<refDim> > vLocGrad;
	MathVector<refDim> locGrad;

//	loop ips
	for(size_t ip = 0; ip < nip; ++ip)
	{
	//	evaluate at shapes at ip
		rTrialSpace.grads(vLocGrad, vLocIP[ip]);

	//	compute grad at ip
		VecSet(locGrad, 0.0);
		for(size_t sh = 0; sh < vLocGrad.size(); ++sh)
			VecScaleAppend(locGrad, (*u)(_C_, sh), vLocGrad[sh]);

		Inverse(JTInv, vJT[ip]);
		MatVecMult(vValue[ip], JTInv, locGrad);

	//	store derivative
		if(bDeriv)
			for(size_t sh = 0; sh < vLocGrad.size(); ++sh)
				MatVecMult(vvvDeriv[ip][_C_][sh], JTInv, vLocGrad[sh]);
	}

	}
	UG_CATCH_THROW("GradientDataExport: Trial space missing, Reference Object: "
				 <<roid<<", Trial Space: "<<lfeID<<", refDim="<<refDim);
}