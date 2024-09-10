	int removeDuplicates(vector<int>& nums) 
    {
    	sort(nums.begin(),nums.end());
    	vector<bool> flags(nums.size(),1);
    	bool flag = 0;
    	for(int i=1; i<nums.size(); ++i)
    	{
    		if(nums[i]!=nums[i-1])
    		{
    			flag = 0;
    		}
    		else
    		{
    			if(flag == 0)
    			{
    				flag = 1;
    			}
    			else
    			{
    				flags[i] =0;
    			}
    		}
    		
    	}
    	vector<int> processed;
    	for(int i=0; i<nums.size(); ++i)
    	{
    		if(flags[i]) processed.push_back(nums[i]);
    	}
    	nums.swap(processed);
    	return nums.size();
    }