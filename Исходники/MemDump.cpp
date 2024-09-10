void KMemDump::Dump(unsigned char * start, unsigned offset, int size, int unitsize)
{
    if ( offset==0 )
    {
	    HANDLE hHeaps[10];
	    int no = GetProcessHeaps(10, hHeaps);
	
        // walk the heap if it is a heap
	    for (int i=0; i<no; i++)
		    if ( start == hHeaps[i] )
		    {
			    PROCESS_HEAP_ENTRY entry;

			    entry.lpData = NULL;

			    while ( HeapWalk(start, & entry) )
			    {
				    wsprintf(m_line, "%x %d+%d bytes %x\r\n", 
                        entry.lpData, entry.cbData,
                        entry.cbOverhead, entry.iRegionIndex);
				
                    * m_stream << m_line;
			    }
			    * m_stream << "\r\n";
			
			    break;
		    }			
    }

	* m_stream << size;
	* m_stream << " bytes\n";
	while (size>0)
	{
		DumpLine(start, offset, unitsize);
		start += 16;
		size  -= 16;

		* m_stream << m_line;
	}
}