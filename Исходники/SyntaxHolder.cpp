bool CSyntaxHolder::GetSentencesFromSynAn(string str, bool bFile)
{
	clock_t t1,t2;
	int CountOfWords;
	
	
	try {
		m_Synan.ClearSentences();
		ClearVector(m_PlmLines.m_Items);

		if (!GetMorphology(str, bFile, CountOfWords))
			return false;;

        #ifdef _DEBUG
		    m_PlmLines.SaveToFile("before.lem");
        #endif
		// ============  Postmorphology =======================

		CPlmLineCollection MapostPlmLines;
		if (m_bTimeStatis) t1= clock();

		if (!m_pPostMorph->ProcessData(&m_PlmLines, MapostPlmLines))
		{
			fprintf (stderr, "  Cannot process Mapost\n");
			return false;

		};;
		if (m_bTimeStatis) 
		{
			t2 = clock();
			double speed =  ((double)CountOfWords)/((t2-t1)/((double)CLOCKS_PER_SEC));
			fprintf(stderr,"Mapost: Ticks = %i Speed = %6.0f\n", t2-t1, speed );
		};


#ifdef _DEBUG
		MapostPlmLines.SaveToFile("after.lem");
#endif
		
		    
		// ============  Syntax =======================
		if (m_bTimeStatis) t1= clock();
		if (!m_Synan.ProcessData(&MapostPlmLines))
		{
			fprintf (stderr, "  Synan has crushed!\n");
			return false;
		};

		if (m_bTimeStatis) 
		{
			t2 = clock();
			double speed =  ((double)CountOfWords)/((t2-t1)/((double)CLOCKS_PER_SEC));
			fprintf(stderr,"Synan: Ticks = %i Speed = %6.0f\n", t2-t1, speed );
		};
		

		return true;
	}
	catch (...)
	{
		return false;
	};
}