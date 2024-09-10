		void swap(fmask& rhs) noexcept
		{
			using std::swap;
			swap(Used, rhs.Used);
			strMask.swap(rhs.strMask);
			FilterMask.swap(rhs.FilterMask);
		}