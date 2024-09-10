	int search(vector<int>& nums, int target) {
		if (nums.empty()) return -1;
		return bSearch(nums, 0, nums.size()-1, target);
	}