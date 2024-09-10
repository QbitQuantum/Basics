 int closestValue(TreeNode* root, double target) {
     stack<TreeNode *> st;
     TreeNode *p = root;
     int res = root->val;
     int val;
     while (true) {
         while (p != NULL) {
             st.push(p);
             p = p->left;
         }
         if (st.empty()) {
             break;
         }
         
         p = st.top()->right;
         val = st.top()->val;
         st.pop();
         
         if (fabs(val - target) < fabs(res - target)) {
             res = val;
         }
         if (val >= target) {
             break;
         }
     }
     while (!st.empty()) {
         st.pop();
     }
     return res;
 }