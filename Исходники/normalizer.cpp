	std::vector<CodePoint> Normalizer::ToNFD (const CodePoint * begin, const CodePoint * end) const {
	
		auto retr=decompose(begin,end);
		
		sort(retr.begin(),retr.end());
		
		return retr;
	
	}