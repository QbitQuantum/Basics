		/// すべてを小文字に変換
		inline WURI &convertLower()
		{
			for(std::wstring::size_type i = 0; i < rn_.size(); i++) {
				if(isleadbyte(rn_[i])) i++;
				else rn_[i] = tolower(rn_[i]);
			}
			return *this;
		}