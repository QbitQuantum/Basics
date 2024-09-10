		void swap(TreeItem& rhs) noexcept
		{
			using std::swap;
			strName.swap(rhs.strName);
			Last.swap(rhs.Last);
			swap(Depth, rhs.Depth);
		}