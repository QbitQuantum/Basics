 double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
     
     if(nums1.empty()&&nums2.empty()) return 0;
     
     int len = nums1.size() + nums2.size();
     
     int big,small;
     
     if(nums1.size()>nums2.size()) {
         big = nums1.size();
         small = nums2.size();
         
     }
     
     else {
         big = nums2.size();
         small = nums1.size();
         nums1.swap(nums2);
     }
     
     if(len%2) {
         return findkstElements(nums1,nums2,0,big,0,small, (len+1)/2);
     }
     
     else {
         return (findkstElements(nums1,nums2,0,big,0,small, len/2) + findkstElements(nums1,nums2,0,big,0,small, len/2+1))/2.0;
     }
     
 }