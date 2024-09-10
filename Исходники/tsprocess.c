void creategraph(void)
{
    /* fill up nodearray with desired nodes: for this benchmark, the
     * details of the graph are hardwired rather than read from
     * file. the graph details are:
       0 (0,0)      {6,11,17}
       1 (100,0)    {6,17}
       2 (200,0)    {8,13}
       3 (300,0)    {5,16}
       4 (400,0)    {12,14,17}
       5 (0,100)    {3,9}
       6 (100,100)  {0,1}
       7 (200,100)  {11,12,15}
       8 (300,100)  {2,14}
       9 (400,100)  {5,11,14}
       10 (0,200)   {13,15}
       11 (100,200) {0,7,9,12,13,16}
       12 (200,200) {4,7,11,13}
       13 (300,200) {2,10,11,12}
       14 (400,200) {4,8,9}
       15 (0,300)   {7,10,16}
       16 (100,300) {3,11,15}
       17 (200,300) {0,1,4}
    */

    int i,x,y,a[NUMNODES];
    Adjptr tmp;

    /* node 0 */
    x = 0; y = 0; a[0] = 6; a[1] = 11; a[2] = 17; a[3] = -1;
    createnode(x,y,a);
    
    /* node 1 */
    x = 100; y = 0; a[0] = 6; a[1] = 17; a[2] = -1;
    createnode(x,y,a);
    
    /* node 2 */
    x = 200; y = 0; a[0] = 8; a[1] = 13; a[2] = -1;
    createnode(x,y,a);
    
    /* node 3 */
    x = 300; y = 0; a[0] = 5; a[1] = 16; a[2] = -1;
    createnode(x,y,a);
    
    /* node 4 */
    x = 400; y = 0; a[0] = 12; a[1] = 14; a[2] = 17; a[3] = -1;
    createnode(x,y,a);
    
    /* node 5 */
    x = 0; y = 100; a[0] = 3; a[1] = 9; a[2] = -1;
    createnode(x,y,a);
    
    /* node 6 */
    x = 100; y = 100; a[0] = 0; a[1] = 1; a[2] = -1;
    createnode(x,y,a);
    
    /* node 7 */
    x = 200; y = 100; a[0] = 11; a[1] = 12; a[2] = 15; a[3] = -1;
    createnode(x,y,a);
    
    /* node 8 */
    x = 300; y = 100; a[0] = 2; a[1] = 14; a[2] = -1;
    createnode(x,y,a);
    
    /* node 9 */
    x = 400; y = 100; a[0] = 5; a[1] = 11; a[2] = 14; a[3] = -1;
    createnode(x,y,a);
    
    /* node 10 */
    x = 0; y = 200; a[0] = 13; a[1] = 15; a[2] = -1;
    createnode(x,y,a);
    
    /* node 11 */
    x = 100; y = 200; a[0] = 0; a[1] = 7; a[2] = 9; a[3] = 12; a[4] = 13; a[5] = 16; a[6] = -1;
    createnode(x,y,a);
    
    /* node 12 */
    x = 200; y = 200; a[0] = 4; a[1] = 7; a[2] = 11; a[3] = 13; a[4] = -1;
    createnode(x,y,a);
    
    /* node 13 */
    x = 300; y = 200; a[0] = 2; a[1] = 10; a[2] = 11; a[3] = 12; a[4] = -1;
    createnode(x,y,a);
    
    /* node 14 */
    x = 400; y = 200; a[0] = 4; a[1] = 8; a[2] = 9; a[3] = -1;
    createnode(x,y,a);
    
    /* node 15 */
    x = 0; y = 300; a[0] = 7; a[1] = 10; a[2] = 16; a[3] = -1;
    createnode(x,y,a);
    
    /* node 16 */
    x = 100; y = 300; a[0] = 3; a[1] = 11; a[2] = 15; a[3] = -1;
    createnode(x,y,a);
    
    /* node 17 */
    x = 200; y = 300; a[0] = 0; a[1] = 1; a[2] = 4; a[3] = -1;
    createnode(x,y,a);

    /* now that all node are set up, compute edge lengths */
    for (i = 0; i < NUMNODES; i++)
    {
	tmp = nodearray[i].adjlist;
	while (tmp != NULL)
	{
	    tmp->edgelength = distance(i,tmp->nodeindex);
	    tmp = tmp->next;
	}
    }
}