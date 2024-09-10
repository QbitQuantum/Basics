void DoOutput( const int num_gardens, 
               List<GardenSummary>& garden_summaries ) {
  // variables
  int garden_num = 1;
  int num_patches = 0;
  int patch_index = 0;
  List<int> patch_list;

  // for every garden given, output ordered patch sizes
  for( garden_num = 1, garden_summaries.gotoBeginning(); 
       garden_num <= num_gardens; ++ garden_num ) {
    // get a pointer for the patch size list and the number of patches
    patch_list = garden_summaries.getCursor().patch_sizes;

    // output the garden number
    cout << "Garden # " << garden_num << ": ";

    // output its number of patches
    num_patches = garden_summaries.getCursor().num_patches;
    cout << num_patches << " patches, ";

    // output each of its patch sizes
      // sort before outputting
      patch_list.BubbleSortL2H();

      // do the output
      cout << "sizes: ";
      for( patch_list.gotoBeginning(), patch_index = 0; patch_index < num_patches;
           ++ patch_index) {
        // output a patch size
        cout << patch_list.getCursor() << " ";

        // move on to the next patch
        patch_list.gotoNext();
      }

    // output one endline
    cout << endl;

    // move to next summary
    garden_summaries.gotoNext();
  }

  // no return - void
}