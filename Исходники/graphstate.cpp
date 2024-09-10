void GraphState::print ( FILE *f ) {
    static int counter = 0;
    counter++;
    putc ( 't', f );
    putc ( ' ', f );
    puti ( f, (int) counter );
    putc ( '\n', f );
    for ( int i = 0; i < (int) nodes.size (); i++ ) {
        putc ( 'v', f );
        putc ( ' ', f );
        puti ( f, (int) i );
        putc ( ' ', f );
        puti ( f, (int) fm::database->nodelabels[nodes[i].label].inputlabel );
        putc ( '\n', f );
    }
    for ( int i = 0; i < (int) nodes.size (); i++ ) {
        for ( int j = 0; j < (int) nodes[i].edges.size (); j++ ) {
            GraphState::GSEdge &edge = nodes[i].edges[j];
            if ( i < edge.tonode ) {
                putc ( 'e', f );
                putc ( ' ', f );
                puti ( f, (int) i );
                putc ( ' ', f );
                puti ( f, (int) edge.tonode );
                putc ( ' ', f );
                puti ( f, (int) fm::database->edgelabels[
                           fm::database->edgelabelsindexes[edge.edgelabel]
                       ].inputedgelabel );
                putc ( '\n', f );
            }
        }
    }
}