		CChunkFileReader::Error Restore()
		{
			// No valid states left.
			if (Empty())
				return CChunkFileReader::ERROR_BAD_FILE;

			int n = (--next_ + size_) % size_;
			if (states_[n].empty())
				return CChunkFileReader::ERROR_BAD_FILE;

			static std::vector<u8> buffer;
			Decompress(buffer, states_[n], bases_[baseMapping_[n]]);
			return LoadFromRam(buffer);
		}