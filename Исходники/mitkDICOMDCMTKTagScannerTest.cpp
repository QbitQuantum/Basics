  void MultiFileScanning()
  {
    mitk::DICOMTagPath instanceUID(0x0008, 0x0018);

    scanner->SetInputFiles(ctFiles);
    scanner->AddTagPath(instanceUID);

    scanner->Scan();

    mitk::DICOMDatasetAccessingImageFrameList frames = scanner->GetFrameInfoList();
    CPPUNIT_ASSERT_MESSAGE("Testing DICOMDCMTKTagScanner::GetFrameInfoList()", frames.size() == 4);

    mitk::DICOMDatasetAccess::FindingsListType findings = frames[0]->GetTagValueAsString(instanceUID);
    CPPUNIT_ASSERT_MESSAGE("Testing DICOMDCMTKTagScanner::GetFrameInfoList()", findings.size() == 1);
    CPPUNIT_ASSERT_MESSAGE("Testing validity of instance uid finding of frame 0", findings.front().isValid);
    CPPUNIT_ASSERT_MESSAGE("Testing path of instance uid finding of frame 0", findings.front().path == instanceUID);
    CPPUNIT_ASSERT_MESSAGE("Testing value of instance uid finding of frame 0", findings.front().value == "1.2.276.0.99.1.4.8323329.3795.1303917947.940051");

    findings = frames[1]->GetTagValueAsString(instanceUID);
    CPPUNIT_ASSERT_MESSAGE("Testing DICOMDCMTKTagScanner::GetFrameInfoList()", findings.size() == 1);
    CPPUNIT_ASSERT_MESSAGE("Testing validity of instance uid finding of frame 1", findings.front().isValid);
    CPPUNIT_ASSERT_MESSAGE("Testing path of instance uid finding of frame 1", findings.front().path == instanceUID);
    CPPUNIT_ASSERT_MESSAGE("Testing value of instance uid finding of frame 1", findings.front().value == "1.2.276.0.99.1.4.8323329.3795.1303917947.940052");

    findings = frames[2]->GetTagValueAsString(instanceUID);
    CPPUNIT_ASSERT_MESSAGE("Testing DICOMDCMTKTagScanner::GetFrameInfoList()", findings.size() == 1);
    CPPUNIT_ASSERT_MESSAGE("Testing validity of instance uid finding of frame 2", findings.front().isValid);
    CPPUNIT_ASSERT_MESSAGE("Testing path of instance uid finding of frame 2", findings.front().path == instanceUID);
    CPPUNIT_ASSERT_MESSAGE("Testing value of instance uid finding of frame 2", findings.front().value == "1.2.276.0.99.1.4.8323329.3795.1303917947.940053");

    findings = frames[3]->GetTagValueAsString(instanceUID);
    CPPUNIT_ASSERT_MESSAGE("Testing DICOMDCMTKTagScanner::GetFrameInfoList()", findings.size() == 1);
    CPPUNIT_ASSERT_MESSAGE("Testing validity of instance uid finding of frame 3", findings.front().isValid);
    CPPUNIT_ASSERT_MESSAGE("Testing path of instance uid finding of frame 3", findings.front().path == instanceUID);
    CPPUNIT_ASSERT_MESSAGE("Testing value of instance uid finding of frame 3", findings.front().value == "1.2.276.0.99.1.4.8323329.3795.1303917947.940055");
  }