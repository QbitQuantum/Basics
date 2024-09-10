int HFinit(HFtree *tree, HTable *terms){

   /* Protect and assign constants */

   ESCAPE_SEQUENCE=ATmake("<str(<appl>)>","ESC","NEW");
   NO_ATERM       =ATmake("<str(<appl>)>","ESC","NIL");
   ATprotect(&ESCAPE_SEQUENCE);
   ATprotect(&NO_ATERM);

   /* Init LZ buffer */

   LZinit(&tree->buffer);

   /* Assign terms table */

   tree->terms=terms;

   /* Create the root node */

   tree->codes=(struct HFnode*)malloc(sizeof(struct HFnode));
   tree->codes->high=NULL;
   tree->codes->parent=NULL;
   tree->codes->frequency=0L;
   tree->codes->term=NULL;

   /* Create the leaf for the escape code */

   tree->codes->low=(struct HFnode*)malloc(sizeof(struct HFnode));
   tree->codes->low->high=NULL;
   tree->codes->low->low=NULL;
   tree->codes->low->parent=tree->codes;
   tree->codes->low->frequency=0L; 
   tree->codes->low->term=ESCAPE_SEQUENCE;

   /* Store the escape sequence term */

   tree->top=tree->codes->low;

   /* Initialise the block list */

   BLinit(&tree->blockList);
   BLinsert(&tree->blockList, tree->codes->low);
   BLinsert(&tree->blockList, tree->codes);

   return 1;
}