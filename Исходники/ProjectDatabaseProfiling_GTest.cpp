// Test not yet to scale re: total data points.
TEST_F(ProjectFixture,Profile_UpdateAnalysis) {
  Analysis analysis = getAnalysisToRun(100,500);

  // save to database
  ProjectDatabase db = getCleanDatabase(toPath("./UpdateAnalysis"));
  ASSERT_TRUE(db.startTransaction());
  AnalysisRecord record(analysis,db);
  db.save();
  ASSERT_TRUE(db.commitTransaction());

  // add output data to 1 data point
  DataPointVector dataPoints = analysis.dataPoints();
  boost::mt19937 mt;
  typedef boost::uniform_real<> uniform_dist_type;
  typedef boost::variate_generator<boost::mt19937&, uniform_dist_type> uniform_gen_type;
  uniform_gen_type responseGenerator(mt,uniform_dist_type(50.0,500.0));
  for (int i = 0; i < 1; ++i) {
    std::stringstream ss;
    ss << "dataPoint" << i + 1;
    DoubleVector responseValues;
    for (int j = 0, n = analysis.problem().responses().size(); j < n; ++j) {
      responseValues.push_back(responseGenerator());
    }
    openstudio::path runDir = toPath(ss.str());
    dataPoints[i] = DataPoint(dataPoints[i].uuid(),
                              createUUID(),
                              dataPoints[i].name(),
                              dataPoints[i].displayName(),
                              dataPoints[i].description(),
                              analysis.problem(),
                              true,
                              false,
                              true,
                              DataPointRunType::Local,
                              dataPoints[i].variableValues(),
                              responseValues,
                              runDir,
                              FileReference(runDir / toPath("ModelToIdf/in.osm")),
                              FileReference(runDir / toPath("ModelToIdf/out.idf")),
                              FileReference(runDir / toPath("EnergyPlus/eplusout.sql")),
                              FileReferenceVector(1u,FileReference(runDir / toPath("Ruby/report.xml"))),
                              boost::optional<runmanager::Job>(),
                              std::vector<openstudio::path>(),
                              TagVector(),
                              AttributeVector());
    dataPoints[i].setName(dataPoints[i].name()); // set dirty
  }
  analysis = Analysis(analysis.uuid(),
                      analysis.versionUUID(),
                      analysis.name(),
                      analysis.displayName(),
                      analysis.description(),
                      analysis.problem(),
                      analysis.algorithm(),
                      analysis.seed(),
                      analysis.weatherFile(),
                      dataPoints,
                      false,
                      false);
  analysis.setName(analysis.name()); // set dirty

  // time the process of updating the database
  ptime start = microsec_clock::local_time();
  db.unloadUnusedCleanRecords();
  ASSERT_TRUE(db.startTransaction());
  record = AnalysisRecord(analysis,db);
  db.save();
  ASSERT_TRUE(db.commitTransaction());
  time_duration updateTime = microsec_clock::local_time() - start;

  std::cout << "Time: " << to_simple_string(updateTime) << std::endl;
}