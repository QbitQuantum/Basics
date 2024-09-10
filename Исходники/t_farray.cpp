LOCAL_C void test2(CArrayFix<TArr<TText,4> >& aFix)
//
	{
	test(aFix.Length()==sizeof(TArr<TText,4>));
	test.Next(_L("AppendL and insert strings of length 4"));
	TPtrC des1=_L("abcd");
	TPtrC des2=_L("efgh");
	aFix.AppendL(*(const TArr<TText,4>*)des1.Ptr());
	aFix.AppendL(*(const TArr<TText,4>*)des2.Ptr());
	test(aFix.Count()==2);
	TPtrC des3(&aFix[0][0],4);
	TPtrC des4(&aFix[1][0],4);
	test(des3==_L("abcd"));
	test(des4==_L("efgh"));
	aFix.InsertL(1,*(const TArr<TText,4>*)_S("ijkl"));
	test(aFix.Count()==3);	
	TPtrC des5(&aFix[2][0],4);
	test(des3==_L("abcd"));
	test(des4==_L("ijkl"));
	test(des5==_L("efgh"));

	test.Next(_L("Reset and Compress"));
	aFix.Reset();
	TBuf<0x10> buf1=_L("abcdefgh");
	aFix.AppendL((const TArr<TText,4>*)buf1.Ptr(),2);
	aFix.Compress();
	TPtrC des6(&aFix[0][0],4);
	test(des6==_L("abcd"));
	TPtrC des7(&aFix[1][0],4);
	test(des7==_L("efgh"));
	buf1=_L("ghighhxy");
	aFix.InsertL(1,(const TArr<TText,4>*)buf1.Ptr(),2);
	aFix.Compress();
	TPtrC des8(&aFix[0][0],4);
	test(des8==_L("abcd"));
	TPtrC des9(&aFix[1][0],4);
	test(des9==_L("ghig"));
	TPtrC des10(&aFix[2][0],4);
	test(des10==_L("hhxy"));
	TPtrC des11(&aFix[3][0],4);
	test(des11==_L("efgh"));

	test.Next(_L("Sort strings"));
	TKeyArrayFix kk(0,ECmpNormal,0x04);
	aFix.Sort(kk);
	TPtrC des12(&aFix[0][0],4);
	test(des12==_L("abcd"));
	TPtrC des13(&aFix[1][0],4);
	test(des13==_L("efgh"));
	TPtrC des14(&aFix[2][0],4);
	test(des14==_L("ghig"));
	TPtrC des15(&aFix[3][0],4);
	test(des15==_L("hhxy"));
	
	test.Next(_L("Find and FindIsq"));
	aFix.Compress();
	test(aFix.InsertIsqL(*(const TArr<TText,4>*)_S("ffff"),kk)==2);
	aFix.Compress();
	test(aFix.InsertIsqAllowDuplicatesL(*(const TArr<TText,4>*)_S("ffff"),kk)==3);
	aFix.Compress();
	TRAPD(r,aFix.InsertIsqL(*(const TArr<TText,4>*)_S("ffff"),kk))
	test(r==KErrAlreadyExists);
	TInt aPos=0;
	test(aFix.Find(*(const TArr<TText,4>*)_S("xxxx"),kk,aPos)==1);
	test(aPos==6);
	test(aFix.Find(*(const TArr<TText,4>*)_S("abcd"),kk,aPos)==0);
	test(aPos==0);
	test(aFix.Find(*(const TArr<TText,4>*)_S("ghig"),kk,aPos)==0);
	test(aPos==4);
	test(aFix.Find(*(const TArr<TText,4>*)_S("ffff"),kk,aPos)==0);
	test(aPos==2);
	test(aFix.Find(*(const TArr<TText,4>*)_S("hhxy"),kk,aPos)==0);
	test(aPos==5);
	test(aFix.FindIsq(*(const TArr<TText,4>*)_S("bbbb"),kk,aPos)!=0);
	test(aPos==1);
	test(aFix.FindIsq(*(const TArr<TText,4>*)_S("abcd"),kk,aPos)==0);
	test(aPos==0);
	test(aFix.FindIsq(*(const TArr<TText,4>*)_S("ghig"),kk,aPos)==0);
	test(aPos==4);
	test(aFix.FindIsq(*(const TArr<TText,4>*)_S("ffff"),kk,aPos)==0);
	test(aPos==2);
	test(aFix.InsertIsqL(*(const TArr<TText,4>*)_S("fghz"),kk)==4);
	test(aFix.FindIsq(*(const TArr<TText,4>*)_S("fghz"),kk,aPos)==0);
	test(aPos==4);
	test(aFix.FindIsq(*(const TArr<TText,4>*)_S("hhxy"),kk,aPos)==0);
	test(aPos==6);
	}