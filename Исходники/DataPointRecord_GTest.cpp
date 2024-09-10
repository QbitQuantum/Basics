TEST_F(ProjectFixture,DataPoint_DataPointRecord_Synchronization) {

  // create analysis with one data point
  ProjectDatabase database = getCleanDatabase("DataPoint_DataPointRecord_Synchronization");

  analysis::Analysis analysis(
      "Test Analysis",
      analysis::Problem("Test Problem",analysis::VariableVector(),runmanager::Workflow()),
      analysis::DesignOfExperiments(analysis::DesignOfExperimentsOptions(
          analysis::DesignOfExperimentsType::FullFactorial)),
      FileReference(toPath("in.osm")));

  std::vector<QVariant> variableValues;
  analysis::DataPoint original = analysis.problem().createDataPoint(variableValues).get();
  analysis.addDataPoint(original);

  // save analysis to database
  {
    bool didStartTransaction = database.startTransaction();
    AnalysisRecord analysisRecord(analysis,database);

    DataPointRecordVector dataPointRecords = DataPointRecord::getDataPointRecords(database);
    ASSERT_EQ(1u,dataPointRecords.size());
    DataPointRecord dataPointRecord = dataPointRecords[0];
    EXPECT_FALSE(dataPointRecord.isComplete());

    database.save();
    if (didStartTransaction) {
      database.commitTransaction();
    }
  }

  // reload analysis, change data point, save back to database
  // verify that change shows up in database
  OptionalAnalysis loadedAnalysis;
  {
    AnalysisRecordVector loadedAnalysisRecords = AnalysisRecord::getAnalysisRecords(database);
    ASSERT_EQ(1u,loadedAnalysisRecords.size());
    loadedAnalysis = loadedAnalysisRecords[0].analysis();

    analysis::DataPointVector loadedDataPoints = loadedAnalysis->dataPoints();
    ASSERT_EQ(1u,loadedDataPoints.size());
    loadedDataPoints[0].getImpl<analysis::detail::DataPoint_Impl>()->markComplete();
    EXPECT_TRUE(loadedDataPoints[0].isComplete());
  }
  ASSERT_TRUE(loadedAnalysis);

  {
    bool didStartTransaction = database.startTransaction();
    database.unloadUnusedCleanRecords();
    AnalysisRecord analysisRecord(*loadedAnalysis,database);
    database.save();
    if (didStartTransaction) {
      database.commitTransaction();
    }
    EXPECT_EQ(1u,AnalysisRecord::getAnalysisRecords(database).size());

    DataPointRecordVector dataPointRecords = DataPointRecord::getDataPointRecords(database);
    ASSERT_EQ(1u,dataPointRecords.size());
    DataPointRecord dataPointRecord = dataPointRecords[0];
    EXPECT_TRUE(dataPointRecord.isComplete());
  }

}