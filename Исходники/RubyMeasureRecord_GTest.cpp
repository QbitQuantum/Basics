TEST_F(ProjectFixture, RubyMeasureRecord_BCLMeasure) {
    // Construct problem with RubyMeasure that points to BCLMeasure
    Problem problem("Problem",VariableVector(),runmanager::Workflow());
    MeasureGroup dvar("Variable",MeasureVector());
    problem.push(dvar);
    openstudio::path measuresPath = resourcesPath() / toPath("/utilities/BCL/Measures");
    openstudio::path dir = measuresPath / toPath("SetWindowToWallRatioByFacade");
    BCLMeasure measure = BCLMeasure::load(dir).get();
    RubyMeasure rpert(measure);
    dvar.push(rpert);
    OSArgument arg = OSArgument::makeDoubleArgument("wwr");
    arg.setValue(0.4);
    rpert.setArgument(arg);
    arg = OSArgument::makeIntegerArgument("typo_arg");
    arg.setDefaultValue(1);
    rpert.setArgument(arg);

    // Serialize to database
    {
        ProjectDatabase database = getCleanDatabase("RubyMeasureRecord_BCLMeasure");

        bool didStartTransaction = database.startTransaction();
        EXPECT_TRUE(didStartTransaction);

        // Problem Record
        ProblemRecord problemRecord = ProblemRecord::factoryFromProblem(problem,database);

        database.save();
        if (didStartTransaction) {
            EXPECT_TRUE(database.commitTransaction());
        }
    }

    // Re-open database, de-serialize, verify that RubyMeasure is intact.
    openstudio::path tempDir1 = measuresPath / toPath(toString(createUUID()));
    {
        ProjectDatabase database = getExistingDatabase("RubyMeasureRecord_BCLMeasure");
        ASSERT_EQ(1u,ProblemRecord::getProblemRecords(database).size());
        ASSERT_EQ(1u,MeasureGroupRecord::getMeasureGroupRecords(database).size());
        EXPECT_EQ(1u,RubyMeasureRecord::getRubyMeasureRecords(database).size());

        MeasureRecordVector dprs = MeasureGroupRecord::getMeasureGroupRecords(database)[0].measureRecords(false);
        ASSERT_EQ(1u,dprs.size());
        ASSERT_TRUE(dprs[0].optionalCast<RubyMeasureRecord>());
        RubyMeasureRecord rpr = dprs[0].cast<RubyMeasureRecord>();
        RubyMeasure rp = rpr.rubyMeasure();
        EXPECT_TRUE(rp.usesBCLMeasure());
        EXPECT_TRUE(rp.measure());
        EXPECT_EQ(dir,rp.measureDirectory());
        EXPECT_EQ(measure.uuid(),rp.measureUUID());
        EXPECT_EQ(measure.versionUUID(),rp.measureVersionUUID());
        EXPECT_ANY_THROW(rp.perturbationScript());
        EXPECT_EQ(2u,rp.arguments().size());
        EXPECT_FALSE(rp.hasIncompleteArguments());

        // Update measure and save
        BCLMeasure newVersion = measure.clone(tempDir1).get();
        newVersion.setDescription("Window to wall ratio with sill height configurable.");
        newVersion.save();
        EXPECT_NE(measure.versionUUID(),newVersion.versionUUID());
        OSArgumentVector args;
        args.push_back(OSArgument::makeDoubleArgument("wwr"));
        args.push_back(OSArgument::makeDoubleArgument("sillHeight"));

        Problem problemCopy = ProblemRecord::getProblemRecords(database)[0].problem();
        problemCopy.updateMeasure(newVersion,args,false);

        bool didStartTransaction = database.startTransaction();
        EXPECT_TRUE(didStartTransaction);

        // Problem Record
        ProblemRecord problemRecord = ProblemRecord::factoryFromProblem(problemCopy,database);

        database.save();
        if (didStartTransaction) {
            EXPECT_TRUE(database.commitTransaction());
        }
    }

    // Re-open database, check that old argument records are gone, check that de-serialized object ok
    openstudio::path tempDir2 = measuresPath / toPath(toString(createUUID()));
    {
        ProjectDatabase database = getExistingDatabase("RubyMeasureRecord_BCLMeasure");
        ASSERT_EQ(1u,ProblemRecord::getProblemRecords(database).size());
        EXPECT_EQ(1u,MeasureGroupRecord::getMeasureGroupRecords(database).size());
        EXPECT_EQ(1u,RubyMeasureRecord::getRubyMeasureRecords(database).size());
        EXPECT_EQ(1u,FileReferenceRecord::getFileReferenceRecords(database).size());
        EXPECT_EQ(2u,OSArgumentRecord::getOSArgumentRecords(database).size());

        Problem problemCopy = ProblemRecord::getProblemRecords(database)[0].problem();
        InputVariableVector vars = problemCopy.variables();
        ASSERT_FALSE(vars.empty());
        ASSERT_TRUE(vars[0].optionalCast<MeasureGroup>());
        MeasureVector dps = vars[0].cast<MeasureGroup>().measures(false);
        ASSERT_FALSE(dps.empty());
        ASSERT_TRUE(dps[0].optionalCast<RubyMeasure>());
        RubyMeasure rp = dps[0].cast<RubyMeasure>();
        EXPECT_TRUE(rp.usesBCLMeasure());
        EXPECT_TRUE(rp.measure());
        EXPECT_EQ(tempDir1,rp.measureDirectory());
        EXPECT_EQ(measure.uuid(),rp.measureUUID());
        EXPECT_NE(measure.versionUUID(),rp.measureVersionUUID());
        EXPECT_ANY_THROW(rp.perturbationScript());
        ASSERT_EQ(2u,rp.arguments().size());
        EXPECT_TRUE(rp.hasIncompleteArguments());
        EXPECT_EQ("wwr",rp.arguments()[0].name());
        ASSERT_EQ(1u,rp.incompleteArguments().size());
        EXPECT_EQ("sillHeight",rp.incompleteArguments()[0].name());

        // Set to different measure
        BCLMeasure measure2 = measure.clone(tempDir2).get();
        measure2.changeUID();
        measure2.incrementVersionId();
        measure2.save();
        measure2 = BCLMeasure::load(tempDir2).get();
        EXPECT_NE(measure.uuid(),measure2.uuid());
        EXPECT_NE(measure.versionUUID(),measure2.versionUUID());
        rp.setMeasure(measure2);
        EXPECT_TRUE(rp.isDirty());
        EXPECT_TRUE(problemCopy.isDirty());

        bool didStartTransaction = database.startTransaction();
        EXPECT_TRUE(didStartTransaction);

        // Problem Record
        ProblemRecord problemRecord = ProblemRecord::factoryFromProblem(problemCopy,database);

        database.save();
        if (didStartTransaction) {
            EXPECT_TRUE(database.commitTransaction());
        }
    }

    // Re-open database, check that old measure and all argument records are gone
    {
        ProjectDatabase database = getExistingDatabase("RubyMeasureRecord_BCLMeasure");
        ASSERT_EQ(1u,ProblemRecord::getProblemRecords(database).size());
        EXPECT_EQ(1u,MeasureGroupRecord::getMeasureGroupRecords(database).size());
        EXPECT_EQ(1u,RubyMeasureRecord::getRubyMeasureRecords(database).size());
        EXPECT_EQ(1u,FileReferenceRecord::getFileReferenceRecords(database).size());
        EXPECT_EQ(0u,OSArgumentRecord::getOSArgumentRecords(database).size());

        Problem problemCopy = ProblemRecord::getProblemRecords(database)[0].problem();
        InputVariableVector vars = problemCopy.variables();
        ASSERT_FALSE(vars.empty());
        ASSERT_TRUE(vars[0].optionalCast<MeasureGroup>());
        MeasureVector dps = vars[0].cast<MeasureGroup>().measures(false);
        ASSERT_FALSE(dps.empty());
        ASSERT_TRUE(dps[0].optionalCast<RubyMeasure>());
        RubyMeasure rp = dps[0].cast<RubyMeasure>();
        EXPECT_TRUE(rp.usesBCLMeasure());
        EXPECT_TRUE(rp.measure());
        EXPECT_EQ(tempDir2,rp.measureDirectory());
        EXPECT_NE(measure.uuid(),rp.measureUUID());
        EXPECT_NE(measure.versionUUID(),rp.measureVersionUUID());
        EXPECT_ANY_THROW(rp.perturbationScript());
        ASSERT_EQ(0u,rp.arguments().size());
        EXPECT_FALSE(rp.hasIncompleteArguments());
    }

    boost::filesystem::remove_all(tempDir1);
    boost::filesystem::remove_all(tempDir2);
}