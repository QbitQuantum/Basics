// Exec_DataSetCmd::Execute()
Exec::RetType Exec_DataSetCmd::Execute(CpptrajState& State, ArgList& argIn) {
  RetType err = CpptrajState::OK;
  if (argIn.Contains("legend")) {         // Set legend for one data set
    std::string legend = argIn.GetStringKey("legend");
    DataSet* ds = State.DSL().GetDataSet( argIn.GetStringNext() );
    if (ds == 0) return CpptrajState::ERR;
    mprintf("\tChanging legend '%s' to '%s'\n", ds->legend(), legend.c_str());
    ds->SetLegend( legend );
  // ---------------------------------------------
  } else if (argIn.hasKey("outformat")) { // Change double precision set output format
    err = ChangeOutputFormat(State, argIn);
  // ---------------------------------------------
  } else if (argIn.hasKey("remove")) {    // Remove data sets by various criteria
    err = Remove(State, argIn);
  // ---------------------------------------------
  } else if (argIn.hasKey("makexy")) {    // Combine values from two sets into 1
    err = MakeXY(State, argIn);
  // ---------------------------------------------
  } else if (argIn.hasKey("make2d")) {    // Create 2D matrix from 1D set
    err = Make2D(State, argIn);
  // ---------------------------------------------
  } else if (argIn.hasKey("vectorcoord")) { // Extract vector X/Y/Z coord as new set
    err = VectorCoord(State, argIn);
  // ---------------------------------------------
  } else if (argIn.hasKey("filter")) {    // Filter points in data set to make new data set
    err = Filter(State, argIn);
  // ---------------------------------------------
  } else if (argIn.hasKey("cat")) {       // Concatenate two or more data sets
    err = Concatenate(State, argIn);
  // ---------------------------------------------
  } else if (argIn.hasKey("droppoints")) { // Drop points from set
    err = ModifyPoints(State, argIn, true);
  // ---------------------------------------------
  } else if (argIn.hasKey("keeppoints")) { // Keep points in set
    err = ModifyPoints(State, argIn, false);
  // ---------------------------------------------
  } else if (argIn.hasKey("dim")) {        // Modify dimension of set(s)
    err = ChangeDim(State, argIn);
  // ---------------------------------------------
  } else if (argIn.hasKey("invert")) {     // Invert set(s) X/Y, create new sets
    err = InvertSets(State, argIn);
  // ---------------------------------------------
  } else {                                // Default: change mode/type for one or more sets.
    err = ChangeModeType(State, argIn);
  }
  return err;
}