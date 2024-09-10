FCPtr BasisEvaluation::getTransformedValuesWithBasisValues(BasisPtr basis, Camellia::EOperator op,
                                                           constFCPtr referenceValues, int numCells,
                                                           BasisCache* basisCache)
{
  typedef FunctionSpaceTools fst;
  //  int numCells = cellJacobian.dimension(0);
  
  int spaceDim = basisCache->getSpaceDim(); // changed 3-21-16
  
  int componentOfInterest;
  Camellia::EFunctionSpace fs = basis->functionSpace();
  Intrepid::EOperator relatedOp = relatedOperator(op,fs,spaceDim, componentOfInterest);
  Teuchos::Array<int> dimensions;
  referenceValues->dimensions(dimensions);
  dimensions.insert(dimensions.begin(), numCells);
  Teuchos::RCP<FieldContainer<double> > transformedValues = Teuchos::rcp(new FieldContainer<double>(dimensions));
  bool vectorizedBasis = functionSpaceIsVectorized(fs);
  if (vectorizedBasis && (op ==  Camellia::OP_VALUE))
  {
    TEUCHOS_TEST_FOR_EXCEPTION( vectorizedBasis && (op ==  Camellia::OP_VALUE),
                               std::invalid_argument, "Vector HGRAD/HVOL with OP_VALUE not supported by getTransformedValuesWithBasisValues.  Please use getTransformedVectorValuesWithComponentBasisValues instead.");
  }
  switch(relatedOp)
  {
    case(Intrepid::OPERATOR_VALUE):
      switch(fs)
    {
      case Camellia::FUNCTION_SPACE_REAL_SCALAR:
        //          cout << "Reference values for FUNCTION_SPACE_REAL_SCALAR: " << *referenceValues;
      case Camellia::FUNCTION_SPACE_HGRAD:
      case Camellia::FUNCTION_SPACE_HGRAD_DISC:
        fst::HGRADtransformVALUE<double>(*transformedValues,*referenceValues);
        break;
      case Camellia::FUNCTION_SPACE_HCURL:
      case Camellia::FUNCTION_SPACE_HCURL_DISC:
        fst::HCURLtransformVALUE<double>(*transformedValues,basisCache->getJacobianInv(),*referenceValues);
        break;
      case Camellia::FUNCTION_SPACE_HDIV:
      case Camellia::FUNCTION_SPACE_HDIV_DISC:
      case Camellia::FUNCTION_SPACE_HDIV_FREE:
        fst::HDIVtransformVALUE<double>(*transformedValues,basisCache->getJacobian(),basisCache->getJacobianDet(),*referenceValues);
        break;
      case Camellia::FUNCTION_SPACE_HVOL:
      case Camellia::FUNCTION_SPACE_HVOL_SPACE_HGRAD_TIME:
      case Camellia::FUNCTION_SPACE_HGRAD_SPACE_HVOL_TIME:
        //        {
        //          static bool haveWarned = false;
        //          if (!haveWarned) {
        //            cout << "WARNING: for the moment, switching to the standard HVOLtransformVALUE method.\n";
        //            haveWarned = true;
        //          }
        //        }
        //          fst::HVOLtransformVALUE<double>(*transformedValues, cellJacobianDet, *referenceValues);
        // for the moment, use the fact that we know the HVOL basis is always an HGRAD basis:
        // (I think using the below amounts to solving for the HVOL variables scaled by Jacobian)
        fst::HGRADtransformVALUE<double>(*transformedValues,*referenceValues);
        break;
      default:
        TEUCHOS_TEST_FOR_EXCEPTION(true,std::invalid_argument, "unhandled transformation");
        break;
    }
      break;
    case(Intrepid::OPERATOR_GRAD):
    case(Intrepid::OPERATOR_D1):
      switch(fs)
    {
      case Camellia::FUNCTION_SPACE_HVOL:
      case Camellia::FUNCTION_SPACE_HGRAD:
      case Camellia::FUNCTION_SPACE_HGRAD_DISC:
        fst::HGRADtransformGRAD<double>(*transformedValues,basisCache->getJacobianInv(),*referenceValues);
        break;
      case Camellia::FUNCTION_SPACE_VECTOR_HVOL:
      case Camellia::FUNCTION_SPACE_VECTOR_HGRAD:
      case Camellia::FUNCTION_SPACE_VECTOR_HGRAD_DISC:
        // referenceValues has dimensions (F,P,D1,D2).  D1 is our component dimension, and D2 is the one that came from the gradient.
        // HGRADtransformGRAD expects (F,P,D) for input, and (C,F,P,D) for output.
        // If we split referenceValues into (F,P,D1=0,D2) and (F,P,D1=1,D2), then we can transform each of those, and then interleave the results…
      {
        // block off so we can create new stuff inside the switch case
        Teuchos::Array<int> dimensions;
        referenceValues->dimensions(dimensions);
        int numFields = dimensions[0];
        int numPoints = dimensions[1];
        int D1 = dimensions[dimensions.size()-2];
        int D2 = dimensions[dimensions.size()-1];
        dimensions[dimensions.size()-2] = D2; // put D2 in the D1 spot
        dimensions.pop_back(); // get rid of original D2
        FieldContainer<double> refValuesSlice(dimensions);
        dimensions.insert(dimensions.begin(),numCells);
        FieldContainer<double> transformedValuesSlice(dimensions);
        
        //          int numEntriesPerSlice = refValuesSlice.size();
        //          int numEntriesPerTransformedSlice = transformedValuesSlice.size();
        
        for (int compIndex1=0; compIndex1<D1; compIndex1++)
        {
          // could speed the following along by doing the enumeration arithmetic in place...
          for (int fieldIndex=0; fieldIndex<numFields; fieldIndex++)
          {
            for (int ptIndex=0; ptIndex<numPoints; ptIndex++)
            {
              for (int compIndex2=0; compIndex2<D2; compIndex2++)
              {
                refValuesSlice(fieldIndex,ptIndex,compIndex2) = (*referenceValues)(fieldIndex,ptIndex,compIndex1,compIndex2);
              }
            }
          }
          
          //            for (int i=0; i<numEntriesPerSlice; i++) {
          //              refValuesSlice[i] = (*referenceValues)[i*D2 + compIndex];
          //            }
          fst::HGRADtransformGRAD<double>(transformedValuesSlice,basisCache->getJacobianInv(),refValuesSlice);
          // could speed the following along by doing the enumeration arithmetic in place...
          for (int cellIndex=0; cellIndex<numCells; cellIndex++)
          {
            for (int fieldIndex=0; fieldIndex<numFields; fieldIndex++)
            {
              for (int ptIndex=0; ptIndex<numPoints; ptIndex++)
              {
                for (int compIndex2=0; compIndex2<D2; compIndex2++)
                {
                  (*transformedValues)(cellIndex,fieldIndex,ptIndex,compIndex1,compIndex2) = transformedValuesSlice(cellIndex,fieldIndex,ptIndex,compIndex2);
                }
              }
            }
          }
          //            for (int i=0; i<numEntriesPerTransformedSlice; i++) {
          //              (*transformedValues)[i*D2 + compIndex] = transformedValuesSlice[i];
          //            }
        }
      }
        
        break;
      default:
        TEUCHOS_TEST_FOR_EXCEPTION(true,std::invalid_argument, "unhandled transformation");
        break;
    }
      break;
    case(Intrepid::OPERATOR_CURL):
      switch(fs)
    {
      case Camellia::FUNCTION_SPACE_HCURL:
      case Camellia::FUNCTION_SPACE_HCURL_DISC:
        if (spaceDim == 2)
        {
          // TODO: confirm that this is correct
          //            static bool warningIssued = false;
          //            if ( ! warningIssued ) {
          //              cout << "WARNING: for HCURL in 2D, transforming with HVOLtransformVALUE. Need to confirm this is correct.\n";
          //              warningIssued = true;
          //            }
          fst::HVOLtransformVALUE<double>(*transformedValues,basisCache->getJacobianDet(), *referenceValues);
        }
        else
        {
          fst::HCURLtransformCURL<double>(*transformedValues,basisCache->getJacobian(),basisCache->getJacobianDet(),*referenceValues);
        }
        break;
      case Camellia::FUNCTION_SPACE_HGRAD:
      case Camellia::FUNCTION_SPACE_HGRAD_DISC:
        // in 2D, HGRADtransformCURL == HDIVtransformVALUE (because curl(H1) --> H(div))
        fst::HDIVtransformVALUE<double>(*transformedValues,basisCache->getJacobian(),basisCache->getJacobianDet(),*referenceValues);
        break;
      case Camellia::FUNCTION_SPACE_VECTOR_HVOL:
      case Camellia::FUNCTION_SPACE_VECTOR_HGRAD:
      case Camellia::FUNCTION_SPACE_VECTOR_HGRAD_DISC: // shouldn't take the transform so late
      default:
        TEUCHOS_TEST_FOR_EXCEPTION(true,std::invalid_argument, "unhandled transformation");
        break;
    }
      break;
    case(Intrepid::OPERATOR_DIV):
      switch(fs)
    {
      case Camellia::FUNCTION_SPACE_HDIV:
      case Camellia::FUNCTION_SPACE_HDIV_DISC:
      case Camellia::FUNCTION_SPACE_HDIV_FREE:
        fst::HDIVtransformDIV<double>(*transformedValues,basisCache->getJacobianDet(),*referenceValues);
        break;
      case Camellia::FUNCTION_SPACE_VECTOR_HVOL:
      case Camellia::FUNCTION_SPACE_VECTOR_HGRAD:
      case Camellia::FUNCTION_SPACE_VECTOR_HGRAD_DISC: // shouldn't take the transform so late
      default:
        TEUCHOS_TEST_FOR_EXCEPTION(true,std::invalid_argument, "unhandled transformation");
        break;
    }
      break;
    case(Intrepid::OPERATOR_D2):
      switch(fs)
    {
      case Camellia::FUNCTION_SPACE_HVOL:
      case Camellia::FUNCTION_SPACE_HGRAD:
      case Camellia::FUNCTION_SPACE_HGRAD_DISC:
      {
        // first term in the sum is:
        //      J^{-1} * OPD2 * J^{-T}
        // where J^{-1} is the inverse Jacabian, and OPD2 is the matrix of reference-space values formed from OP_D2
        
        const FieldContainer<double> *J_inv = &basisCache->getJacobianInv();
        transformedValues->initialize(0.0);
        int basisCardinality = basis->getCardinality();
        
        Teuchos::Array<int> multiplicities(spaceDim);
        Teuchos::Array<int> multiplicitiesTransformed(spaceDim);
        int dkCardinality = Intrepid::getDkCardinality(Intrepid::OPERATOR_D2, spaceDim);
        int numPoints = referenceValues->dimension(1);
        
        for (int cellOrdinal=0; cellOrdinal<numCells; cellOrdinal++)
        {
          for (int fieldOrdinal=0; fieldOrdinal<basisCardinality; fieldOrdinal++)
          {
            for (int pointOrdinal=0; pointOrdinal<numPoints; pointOrdinal++)
            {
              for (int dkOrdinal=0; dkOrdinal<dkCardinality; dkOrdinal++) // ref values dkOrdinal
              {
                double refValue = (*referenceValues)(fieldOrdinal,pointOrdinal,dkOrdinal);
                Intrepid::getDkMultiplicities(multiplicities, dkOrdinal, Intrepid::OPERATOR_D2, spaceDim);
                int k,l; // ref space coordinate directions for refValue (columns in J_inv)
                getD2_ij_FromMultiplicities(k,l,multiplicities);
                
                for (int dkOrdinalTransformed=0; dkOrdinalTransformed<dkCardinality; dkOrdinalTransformed++) // physical values dkOrdinal
                {
                  Intrepid::getDkMultiplicities(multiplicitiesTransformed, dkOrdinalTransformed, Intrepid::OPERATOR_D2, spaceDim);
                  int i,j; // physical space coordinate directions for refValue (rows in J_inv)
                  getD2_ij_FromMultiplicities(i,j,multiplicitiesTransformed);
                  double J_inv_ik = (*J_inv)(cellOrdinal,pointOrdinal,i,k);
                  double J_inv_jl = (*J_inv)(cellOrdinal,pointOrdinal,j,l);
                  (*transformedValues)(cellOrdinal,fieldOrdinal,pointOrdinal,dkOrdinalTransformed) += refValue * J_inv_ik * J_inv_jl;
                }
              }
            }
          }
        }
        
        // do we need the second term in the sum?  (So far, we don't support this)
        if (!basisCache->neglectHessian())
        {
          // then we need to do include the gradient of the basis times the (inverse) of the Hessian
          // this seems complicated, and we don't need it for computing the Laplacian in physical space
          // (at least not unless we have curvilinear geometry) so we don't support it for now...
          TEUCHOS_TEST_FOR_EXCEPTION(!basisCache->neglectHessian(), std::invalid_argument, "Support for the Hessian of the reference-to-physical mapping not yet implemented.");
        }
      }
        break;
      default:
        TEUCHOS_TEST_FOR_EXCEPTION(true,std::invalid_argument, "unhandled transformation");
        break;
    }
      break;

    default:
      TEUCHOS_TEST_FOR_EXCEPTION(true,std::invalid_argument, "unhandled transformation");
      break;
  }
  
  FCPtr result = getComponentOfInterest(transformedValues,op,fs,componentOfInterest);
  if ( result.get() == 0 )
  {
    result = transformedValues;
  }
  return result;
}