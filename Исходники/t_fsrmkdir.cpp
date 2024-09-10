/** Delete entry in directory

*/
LOCAL_C TInt DeleteEntryAccess2(TAny* )
	{
	RFs fs;
	TInt r = fs.Connect();
	TBuf<100> dirfile;
	TBuf<50> filename;
	RFile file;
	RTest test(_L("test 2")); 

	fs.SetSessionPath(gSessionPath);
	filename.Format(KDeleteMe2, gT2);
	
	dirfile = gDelEntryDir2;
	dirfile.Append(filename);
	
	client.Signal();
	
	FOREVER
		{
			if(!gKillMe)
				{
				r = file.Create(fs, dirfile, EFileShareAny|EFileWrite);
				if(r == KErrAlreadyExists) 
					r=file.Open(fs, dirfile, EFileShareAny|EFileWrite);
				file.Close();
				FailIfError(r);
				
				r = fs.Delete(dirfile);
				if((r != KErrNone) && (r != KErrInUse)) 
					{
					test.Printf(_L("error = %d\n"), r);
					}
				test(r == KErrNone || r == KErrInUse);
			}
		}
	}