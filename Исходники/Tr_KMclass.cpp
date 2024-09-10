//----------------------------------------------------------------------------------
bool TrKMclass::AdjustMemoryLimits()
{
	FILE* pFile = NULL;
	if((pFile = fopen(data_file_name.c_str(), "rb")) == NULL)
	{
		perror("fopen");
		cout << data_file_name.c_str() << "\n";
		return false;
	}
	fread(&kmer_len, 1, 1, pFile);
	
	
	#ifdef WIN32
		_fseeki64(pFile, 0L, SEEK_END); //Windows
		uint64 len_all = _ftelli64(pFile) - 8;// windows
		_fseeki64(pFile, len_all, SEEK_SET); // windows		
	#else
		fseeko(pFile, 0L, SEEK_END);   // linux
		uint64 len_all = ftello(pFile) - 8; // linux
		fseeko(pFile, len_all, SEEK_SET); // linux	 
	#endif
	
	//max_mem_binsKMER = ftell(pFile) + 256*256*8 + 100; // pamiec dla struktury z wszystkimi kmerami wczytanymi
	 
	num_kmer=0;
	fread(&num_kmer, 1, sizeof(uint64), pFile); 
	max_mem_binsKMER = 256 * (1 + 8 + 8*256 + 8) + 8 * num_kmer;
	cout << "   No. of kmer: " << setw(12) << num_kmer << "\n";

	fclose(pFile);
	
	if (max_mem_size <= max_mem_binsKMER)
	{
		cout << "max_mem_size <= max_mem_binsKMER\n";
		return false;
	}
	uint64 m_rest = max_mem_size - max_mem_binsKMER;
	max_mem_seqKMER   = m_rest; //wczytywane sekwencje z kmerami
	

	//part 2
	m_rest = max_mem_size - max_mem_binsKMER;


#ifdef DEBUG_MODE	
	cout << "Splitters: " << m_splitters << "\n";
	//cout << "Storer   : " << max_mem_storer << "\n";
	cout << "FASTQ    : " << max_mem_fastq << "\n";
	cout << "READS    : " << max_mem_reads << "\n";
	//cout << "Bin part : " << max_mem_bin_part << "\n";
	cout << "Stage 2  : " << max_mem_stage2 << "\n";
#endif


	//if(max_mem_fastq < 2 * (uint32)fastq_buffer_size)
	//{
	//	cout << "max_mem_fastq < 2 * (uint32)fastq_buffer_size \n";
	//	return false;
	//}

	
	return true;
}