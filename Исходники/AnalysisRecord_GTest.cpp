TEST_F(ProjectFixture,AnalysisRecord_SetProblem) {
  // create an analysis with data points
  Problem problem1("Minimal Problem",VariableVector(),runmanager::Workflow());
  Analysis analysis("Analysis",
                    problem1,
                    FileReferenceType::OSM);
  OptionalDataPoint dataPoint = problem1.createDataPoint(std::vector<QVariant>());
  ASSERT_TRUE(dataPoint);
  bool test = analysis.addDataPoint(*dataPoint);
  EXPECT_TRUE(test);

  // save to database, make sure everything is there, make sure clean signal filters down
  ProjectDatabase database = getCleanDatabase("AnalysisRecord_SetProblem");
  {
    bool transactionStarted = database.startTransaction();
    EXPECT_TRUE(transactionStarted);
    AnalysisRecord analysisRecord(analysis,database);
    database.save();
    test = database.commitTransaction();
    EXPECT_TRUE(test);
    ASSERT_NO_THROW(analysisRecord.problemRecord());
    ProblemRecord problemRecord = analysisRecord.problemRecord();
    EXPECT_EQ(problem1.uuid(),problemRecord.handle());
    EXPECT_EQ(problem1.versionUUID(),problemRecord.uuidLast());
    EXPECT_EQ(1u,analysisRecord.dataPointRecords().size());
  }
  analysis.clearDirtyFlag();
  EXPECT_FALSE(analysis.isDirty());
  EXPECT_FALSE(problem1.isDirty());
  BOOST_FOREACH(const DataPoint& dataPoint, analysis.dataPoints()) {
    EXPECT_FALSE(dataPoint.isDirty());
  }
  EXPECT_FALSE(analysis.dataPointsAreInvalid());

  // set analysis to have new problem
  // make sure dirty flag bubbles up, data points marked invalid
  Problem problem2 = problem1.clone().cast<Problem>();
  problem2.setName("Real Problem");
  EXPECT_NE(problem1.uuid(),problem2.uuid());
  analysis.setProblem(problem2);
  EXPECT_TRUE(analysis.isDirty());
  EXPECT_FALSE(problem1.isDirty());
  EXPECT_TRUE(problem2.isDirty());
  EXPECT_TRUE(analysis.dataPointsAreInvalid());
  RubyPerturbation userScript(toPath("measure.rb"),
                              FileReferenceType::IDF,
                              FileReferenceType::IDF,
                              true);
  RubyContinuousVariable cvar("Script Argument Variable",
                              ruleset::OSArgument::makeDoubleArgument("COP"),
                              userScript);
  test = problem2.push(cvar);
  EXPECT_FALSE(test); // IDF not compatible with seed
  EXPECT_TRUE(problem2.variables().empty());
  test = userScript.setPerturbationScript(toPath("measure.rb"),
                                          FileReferenceType::OSM,
                                          FileReferenceType::OSM,
                                          true);
  EXPECT_TRUE(test);
  test = problem2.push(cvar);
  EXPECT_TRUE(test);
  EXPECT_EQ(1u,analysis.problem().variables().size());
  EXPECT_EQ(1u,analysis.dataPoints().size());
  dataPoint = problem2.createDataPoint(std::vector<QVariant>(1u,3.5));
  ASSERT_TRUE(dataPoint);
  test = analysis.addDataPoint(*dataPoint);
  EXPECT_FALSE(test);

  // save to database, make sure dataPointsAreInvalid flag was saved, old problem
  // should still be there, new problem there, and clean signal won't go through
  Analysis analysisCopy = analysis; // will replace with deserialized version momentarily
  {
    bool transactionStarted = database.startTransaction();
    EXPECT_TRUE(transactionStarted);
    database.unloadUnusedCleanRecords(); // ETH@20130201 - Having to call this is awkward.
                                         // (As are the brackets) Where is the best place?
    AnalysisRecord analysisRecord(analysis,database);
    database.save();
    test = database.commitTransaction();
    EXPECT_TRUE(test);
    ASSERT_NO_THROW(analysisRecord.problemRecord());
    ProblemRecord problemRecord = analysisRecord.problemRecord();
    EXPECT_EQ(problem2.uuid(),problemRecord.handle());
    EXPECT_EQ(problem2.versionUUID(),problemRecord.uuidLast());
    EXPECT_EQ(2u,ProblemRecord::getProblemRecords(database).size()); // old one still around
    EXPECT_EQ(1u,analysisRecord.dataPointRecords().size());
    test = analysis.clearDirtyFlag();
    EXPECT_FALSE(test);
    Analysis analysisCopy = analysisRecord.analysis(); // should work b/c both problems around
  }
  EXPECT_EQ(analysis.uuid(),analysisCopy.uuid());
  EXPECT_EQ(analysis.versionUUID(),analysisCopy.versionUUID());
  EXPECT_TRUE(analysisCopy.isDirty());
  EXPECT_TRUE(analysisCopy.dataPointsAreInvalid());
  ASSERT_FALSE(analysisCopy.dataPoints().empty());
  EXPECT_NE(analysisCopy.problem().uuid(),analysisCopy.dataPoints()[0].problem().uuid());
  test = analysisCopy.clearDirtyFlag();
  EXPECT_FALSE(test);

  // remove data points, save again, make sure dataPointsAreInvalid flag a-okay, new problem
  // still there and ok, old problem is going to hang around because didn't get rid of it when
  // analysisRecord still pointing to it, clean signal filters all the way down
  analysisCopy.removeAllDataPoints();
  {
    bool transactionStarted = database.startTransaction();
    EXPECT_TRUE(transactionStarted);
    database.unloadUnusedCleanRecords(); // ETH@20130201 - Having to call this is awkward.
                                         // Where is the best place?
    AnalysisRecord analysisRecord(analysisCopy,database);
    database.save();
    test = database.commitTransaction();
    EXPECT_TRUE(test);
    ASSERT_NO_THROW(analysisRecord.problemRecord());
    ProblemRecord problemRecord = analysisRecord.problemRecord();
    EXPECT_EQ(problem2.uuid(),problemRecord.handle());
    EXPECT_EQ(problem2.versionUUID(),problemRecord.uuidLast());
    // old problem record still hanging around.
    // TODO: Have use count as child, resource, and be able to (selectively) purge.
    EXPECT_EQ(2u,ProblemRecord::getProblemRecords(database).size());
    EXPECT_TRUE(analysisRecord.dataPointRecords().empty());
    analysis = analysisRecord.analysis();
  }
  test = analysis.clearDirtyFlag();
  EXPECT_TRUE(test);
  EXPECT_FALSE(analysis.isDirty());
  EXPECT_FALSE(analysis.dataPointsAreInvalid());
  EXPECT_FALSE(analysis.resultsAreInvalid());
  EXPECT_TRUE(analysis.dataPoints().empty());
}