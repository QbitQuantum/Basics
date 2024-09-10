	bool bSearch(int A[], int left, int right, int target)
	{
		if(left < 0 || right < 0)return false;
		if(left > right)return false;

		int mid = (left + right) >> 1;
		if(A[mid] == target)return true;
		if(A[mid] < target)return bSearch(A, mid + 1, right, target);
		if(A[mid] > target)return bSearch(A, left, mid - 1, target);
	}