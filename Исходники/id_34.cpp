 vector<int> searchRange(int A[], int n, int target) {
     int idx = bSearch(A, 0, n, target);
     vector<int> res;
     if (idx == -1) {
         res.push_back(-1);
         res.push_back(-1);
         return res;
     }
     int tmp1(idx), tmp2(idx);
     tmp1 = getLeft(A, 0, idx, target);
     tmp2 = getRight(A, idx, n-1, target);
     res.push_back(tmp1);
     res.push_back(tmp2);
     return res;
 }