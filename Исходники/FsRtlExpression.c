static VOID FsRtlIsDbcsInExpressionTest()
{
    ULONG i;
    for (i = 0; i < sizeof(Tests) / sizeof(Tests[0]); i++)
    {
        BOOLEAN TestResult;
        UNICODE_STRING UExpression;
        UNICODE_STRING UName;
        ANSI_STRING Expression;
        ANSI_STRING Name;

        /* Don't run Tests which are known to assert in checked builds */
        if (KmtIsCheckedBuild && Tests[i].AssertsInChecked)
            continue;

        /* Ignore Tests flagged IgnoreCase==TRUE to avoid duplicated testing */
        if (Tests[i].IgnoreCase)
            continue;

        RtlInitUnicodeString(&UExpression, Tests[i].Expression);
        RtlInitUnicodeString(&UName, Tests[i].Name);

        RtlUnicodeStringToAnsiString(&Expression, &UExpression, TRUE);
        RtlUnicodeStringToAnsiString(&Name, &UName, TRUE);

        TestResult = FsRtlIsDbcsInExpression(&Expression, &Name);

        ok(TestResult == Tests[i].Expected, "FsRtlIsDbcsInExpression(%Z,%Z): Expected %s, got %s\n",
           &Expression, &Name, Tests[i].Expected ? "TRUE" : "FALSE", TestResult ? "TRUE" : "FALSE");

        RtlFreeAnsiString(&Expression);
        RtlFreeAnsiString(&Name);
    }
}