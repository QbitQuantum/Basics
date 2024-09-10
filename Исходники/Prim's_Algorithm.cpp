int main()
{
    Graph G;int src = 1;
    Timer t;clrscr();
    G.input();
    cout << "Give the source node (where to start) : ";cin >> src;
    t.start();G.start_PRIMS_frm(src);t.stop();
    G.printTree();
    cout << "\nTime taken for this is : " << t.time() << " seconds\n";
    //G.randomize();                      //uncomment this only for bulk operation
    getch();
    return 0;
}