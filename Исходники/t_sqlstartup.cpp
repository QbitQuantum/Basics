/**
@SYMTestCaseID          PDS-SQL-UT-4161
@SYMTestCaseDesc        SQL server startup file I/O error simulation test
@SYMTestPriority        High
@SYMTestActions         Runs the SQL server startup code in a file I/O error simulation loop.
@SYMTestExpectedResults Test must not fail
@SYMDEF                 DEF144096
*/  
void SqlServerStartupFileIoErrorTest()
    {
    RFs fs;
    TInt err = fs.Connect();
    TEST2(err, KErrNone);
    
    for(TInt fsError=KErrNotFound;fsError>=KErrBadName;--fsError)
        {
        TheTest.Printf(_L("===Simulated error: %d\r\nIteration: "), fsError);
        err = KErrNotFound;
        TInt cnt=0;
        while(err<KErrNone)
            {
            TheTest.Printf(_L("%d "), cnt);
            (void)fs.SetErrorCondition(fsError, cnt);
            TRAP(err, CreateAndDestroySqlServerL());
            (void)fs.SetErrorCondition(KErrNone);
            if(err != KErrNone)
                {
                ++cnt;
                }
            }
        TEST2(err, KErrNone);
        TheTest.Printf(_L("\r\n===File I/O error simulation test succeeded on iteration %d===\r\n"), cnt);
        }

    fs.Close();
    }