int main(int argc, char** argv)
{
//   TestCertClient Parameters
//       Parameter 1: Client Certification File
//       Parameter 2: Client Private Key File
//       Parameter 3: Random Key File
//       Parameter 4: User Name
//       Parameter 5: Password
//       Parameter 6: Expected Result
//       Parameter 7: Expected Identity

    if ((argc < 3) || (argc > 8))
    {
        PEGASUS_STD(cout) << "Wrong number of arguments" << PEGASUS_STD(endl);
        exit(1);
    }

    String certpath;
    if (strcmp(argv[1],"NONE") != 0)
    {
        certpath = argv[1];
    }

    String keypath;
    if (strcmp(argv[2],"NONE") != 0)
    {
        keypath = argv[2];
    }

    String randFile;
    if (argc >=4)
    {
        if (strcmp(argv[3],"CONFIG") == 0)
        {
            const char* pegasusHome = getenv("PEGASUS_HOME");
            randFile = FileSystem::getAbsolutePath(
                pegasusHome, PEGASUS_SSLCLIENT_RANDOMFILE);
        }
        else if (strcmp(argv[3],"NONE") != 0)
        {
            randFile = argv[3];
        }
    }

    String userName;
    if (argc >=  5)
    {
        userName = argv[4];
    }

    String password;
    if (argc >=  6)
    {
        password = argv[5];
    }

    expectedResultType expectedResult = NONE;
    expectedErrorType expectedError = ERROR_TYPE_NONE;
    String expectedUserName;
    if (argc >=  7)
    {
        if (strcmp(argv[6],"PASS") == 0)
        {
            expectedResult = PASS;
            if (argc >= 8)
            {
               if (strcmp(argv[7],"NONE") != 0)
               {
                   expectedUserName = argv[7];
               }
            }
        }
        else if (strcmp(argv[6],"FAIL") == 0)
        {
            expectedResult = FAIL;
            if (argc >= 8)
            {
               if (strcmp(argv[7],"NONE") == 0)
               {
                   expectedError = ERROR_TYPE_NONE;
               }
               else if (strcmp(argv[7],"HTTP_401") == 0)
               {
                   expectedError = ERROR_TYPE_HTTP_401;
               }
               else if (strcmp(argv[7],"CANNOT_CONNECT") == 0)
               {
                   expectedError = ERROR_TYPE_CANNOT_CONNECT;
               }
               else
               {
                   PEGASUS_STD(cout) << "Invalid expectedError parameter: "
                        << argv[7] << PEGASUS_STD(endl);
                   exit(1);
               }
            }
        }
        else if (strcmp(argv[6],"NONE") == 0)
        {
            expectedResult = NONE;
        }
        else
        {
            PEGASUS_STD(cout) << "Invalid expectedResult parameter: "
                << argv[6] << PEGASUS_STD(endl);
            exit(1);
        }
    }

    try
    {
        AutoPtr<SSLContext> pCtx;
        if (certpath != String::EMPTY)
        {
            pCtx.reset(
                new SSLContext(String::EMPTY, certpath, keypath, 0, randFile));
        }
        else
        {
            pCtx.reset(new SSLContext(String::EMPTY, 0, randFile));
        }

        PEGASUS_STD(cout)<< "TestCertClient::Connecting to 127.0.0.1:5989"
          << PEGASUS_STD(endl);
    
        CIMClient client;
        client.connect("127.0.0.1", 5989, *pCtx, userName, password);

        Array<CIMParamValue> inParams;
        Array<CIMParamValue> outParams;
        CIMValue retValue = client.invokeMethod(
            CIMNamespaceName("test/TestProvider"),
            CIMObjectPath("Test_MethodProviderClass"),
            CIMName("getIdentity"),
            inParams,
            outParams);

        if (expectedResult == FAIL)
        {
           throw Exception("Failure: Connection unexpectedly succeeded");
        }

        String retUserName;
        retValue.get(retUserName);

        if (expectedUserName != String::EMPTY)
        {
           if (expectedUserName != retUserName)
           {
              throw Exception("Provider returned unexpected Identity: "
                  + retUserName);
           }
        }
        CIMClass c = client.getClass("root/cimv2",
            "CIM_ComputerSystem", false, false, true);
          
        PEGASUS_STD(cout) << "Result: " <<  c.getClassName().getString()
            << PEGASUS_STD(endl);
    }
    catch (CIMClientHTTPErrorException& httpException)
    {
        if ((expectedResult == FAIL) &&
                (httpException.getCode() == 401) &&
                (expectedError == ERROR_TYPE_HTTP_401))
        {
            PEGASUS_STD(cout) << "+++++ "<< argv[0] <<
                " +++++ passed all tests" << PEGASUS_STD(endl);
            exit(0);
         }
           
         PEGASUS_STD(cout) << "Exception: " << httpException.getMessage()
            << PEGASUS_STD(endl);
         exit(1);
    }
    catch (CannotConnectException& connectException)
    {
        if ((expectedResult == FAIL) &&
                (expectedError == ERROR_TYPE_CANNOT_CONNECT))
        {
            PEGASUS_STD(cout) << "+++++ "<< argv[0] <<
                " +++++ passed all tests" << PEGASUS_STD(endl);
            exit(0);
        }
        PEGASUS_STD(cout) << "Exception: " << connectException.getMessage()
            << PEGASUS_STD(endl);
        exit(1);
    }
    catch (Exception& ex)
    {
        PEGASUS_STD(cout) << "Exception: " << ex.getMessage()
             << PEGASUS_STD(endl);
        exit(1);

    }
    catch (...)
    {
        PEGASUS_STD(cout) << "Unknown exception" << PEGASUS_STD(endl);
        exit(1);
    }
    if (expectedResult == PASS)
    {
        PEGASUS_STD(cout) << "+++++ "<< argv[0] <<
             " +++++ passed all tests" << PEGASUS_STD(endl);
    }
    else
    {
        PEGASUS_STD(cout) << "+++++ "<< "TestCertClient" 
            << " Terminated Normally" << PEGASUS_STD(endl);
    }
    exit(0);
}