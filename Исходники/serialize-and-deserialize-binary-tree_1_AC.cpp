 TreeNode *deserializeTraverse(const string &s, int &idx) {
     int ls = s.size();
     if (idx >= ls) {
         return NULL;
     }
     
     TreeNode *root;
     
     if (s[idx] == CHAR_NULL) {
         root = NULL;
         idx += 2;
         return root;
     }
     
     int val = 0;
     string s1 = "";
     while (idx < ls && s[idx] != CHAR_SPC) {
         s1.push_back(s[idx++]);
     }
     sscanf(s1.data(), "%d", &val);
     ++idx;
     
     root = new TreeNode(val);
     root->left = deserializeTraverse(s, idx);
     root->right = deserializeTraverse(s, idx);
     
     return root;
 }