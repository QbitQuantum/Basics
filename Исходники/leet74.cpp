		bool searchMatrix(vector<vector<int> > &mat, int target)
		{
			int n = mat.size();
			if (!n) return false;
			int m = mat[0].size();
			if (!m) return false;

			vector<int> l;
			for (int i = 0; i < n; i++)
				l.push_back(mat[i][m - 1]);

			int id = bSearch(l, target);
			if (id >= n)
				return false;

			int ret = bSearch(mat[id], target);
			if (ret >= m)
				return false;

			//printf ("[id=%d][ret=%d] = %d\n", id, ret, mat[id][ret]);
			return mat[id][ret] == target;
		}