void TestAsset2::PopulateStructure( Reflect::Structure& comp )
{
    comp.AddField(            &TestAsset2::m_TestValue1,               TXT( "m_TestValue1" ) );
    comp.AddField(            &TestAsset2::m_TestReference,            TXT( "m_TestReference" ), Reflect::FieldFlags::Share );
    comp.AddField(            &TestAsset2::m_TestDeepCopy,             TXT( "m_TestDeepCopy" ) );
}