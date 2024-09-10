// ======================================================================
void GetPtent(const Operator& A, Teuchos::ParameterList& List,
              const MultiVector& ThisNS,
              Operator& Ptent, MultiVector& NextNS)
{
  std::string CoarsenType     = List.get("aggregation: type", "Uncoupled");
  /* old version
  int    NodesPerAggr    = List.get("aggregation: per aggregate", 64);
  */
  double Threshold       = List.get("aggregation: threshold", 0.0);
  int    NumPDEEquations = List.get("PDE equations", 1);

  ML_Aggregate* agg_object;
  ML_Aggregate_Create(&agg_object);
  ML_Aggregate_Set_MaxLevels(agg_object,2);
  ML_Aggregate_Set_StartLevel(agg_object,0);
  ML_Aggregate_Set_Threshold(agg_object,Threshold);
  //agg_object->curr_threshold = 0.0;

  ML_Operator* ML_Ptent = 0;
  ML_Ptent = ML_Operator_Create(GetML_Comm());

  if (ThisNS.GetNumVectors() == 0)
    ML_THROW("zero-dimension null space", -1);

  int size = ThisNS.GetMyLength();

  double* null_vect = 0;
  ML_memory_alloc((void **)(&null_vect), sizeof(double) * size * ThisNS.GetNumVectors(), "ns");

  int incr = 1;
  for (int v = 0 ; v < ThisNS.GetNumVectors() ; ++v)
    DCOPY_F77(&size, (double*)ThisNS.GetValues(v), &incr,
              null_vect + v * ThisNS.GetMyLength(), &incr);


  ML_Aggregate_Set_NullSpace(agg_object, NumPDEEquations,
                             ThisNS.GetNumVectors(), null_vect,
                             ThisNS.GetMyLength());

  if (CoarsenType == "Uncoupled")
    agg_object->coarsen_scheme = ML_AGGR_UNCOUPLED;
  else if (CoarsenType == "Uncoupled-MIS")
    agg_object->coarsen_scheme = ML_AGGR_HYBRIDUM;
  else if (CoarsenType == "MIS") {
   /* needed for MIS, otherwise it sets the number of equations to
    * the null space dimension */
    agg_object->max_levels  = -7;
    agg_object->coarsen_scheme = ML_AGGR_MIS;
  }
  else if (CoarsenType == "METIS")
    agg_object->coarsen_scheme = ML_AGGR_METIS;
  else {
    ML_THROW("Requested aggregation scheme (" + CoarsenType +
             ") not recognized", -1);
  }

  int NextSize = ML_Aggregate_Coarsen(agg_object, A.GetML_Operator(),
                                      &ML_Ptent, GetML_Comm());

  /* This is the old version
  int NextSize;

  if (CoarsenType == "Uncoupled") {
    NextSize = ML_Aggregate_CoarsenUncoupled(agg_object, A.GetML_Operator(),
  }
  else if (CoarsenType == "MIS") {
    NextSize = ML_Aggregate_CoarsenMIS(agg_object, A.GetML_Operator(),
                                       &ML_Ptent, GetML_Comm());
  }
  else if (CoarsenType == "METIS") {
    ML ml_object;
    ml_object.ML_num_levels = 1; // crap for line below
    ML_Aggregate_Set_NodesPerAggr(&ml_object,agg_object,0,NodesPerAggr);
    NextSize = ML_Aggregate_CoarsenMETIS(agg_object, A.GetML_Operator(),
                                         &ML_Ptent, GetML_Comm());
  }
  else {
    ML_THROW("Requested aggregation scheme (" + CoarsenType +
             ") not recognized", -1);
  }
  */

  ML_Operator_ChangeToSinglePrecision(ML_Ptent);

  int NumMyElements = NextSize;
  Space CoarseSpace(-1,NumMyElements);
  Ptent.Reshape(CoarseSpace,A.GetRangeSpace(),ML_Ptent,true);

  assert (NextSize * ThisNS.GetNumVectors() != 0);

  NextNS.Reshape(CoarseSpace, ThisNS.GetNumVectors());

  size = NextNS.GetMyLength();
  for (int v = 0 ; v < NextNS.GetNumVectors() ; ++v)
    DCOPY_F77(&size, agg_object->nullspace_vect + v * size, &incr,
              NextNS.GetValues(v), &incr);

  ML_Aggregate_Destroy(&agg_object);
  ML_memory_free((void**)(&null_vect));
}