OctreeNode*
sps_real(CBface_list& input_faces,
         CBBOX& box,
         int height,
         double regularity,
         double min_dist,
         Bface_list& flist,
         ARRAY<Wvec>& blist,
         double& spacing
   ) 
{
   clock_t start, end;
   double duration; 
   flist.clear();
   blist.clear();

   OctreeNode* root = new OctreeNode(box.min(), box.max(), 1, NULL);
   if (height == 1) {
      root->set_leaf(true);
      root->set_disp(true);
   }
   root->intersects() = input_faces;

   start = clock();
   root->build_octree(height);
   end = clock();   
  
   duration = (double)(end - start) / CLOCKS_PER_SEC;
   err_adv(debug, "step 1 time: %f", duration); 
  
   start = clock();
   visit(root, regularity, flist, blist);
   end = clock();
   duration = (double)(end - start) / CLOCKS_PER_SEC;
   err_adv(debug, "step 2 time: %f", duration);

   // remove bad samples
   start = clock();
   double dist = min_dist * box.dim().length() / (1<<(height-1));
   spacing = dist;
   root->set_neibors();

   root->set_terms();

   remove_nodes(flist, blist, dist, root->terms());
   end = clock();
   duration = (double)(end - start) / CLOCKS_PER_SEC;
   err_adv(debug, "step 3 time: %f", duration);   
   err_adv(debug, "no of points: %d", flist.num());

   return root;
}