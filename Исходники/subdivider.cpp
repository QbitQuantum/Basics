void
Subdivider::drawSurfaces( long nuid )
{
    renderhints.init( );

    if (qlist == NULL) return;
    for( Quilt *q = qlist; q; q = q->next ) {
	if( q->isCulled( ) == CULL_TRIVIAL_REJECT ) {
	    freejarcs( initialbin );
	    return;
	}
    }

    REAL from[2], to[2];
    qlist->getRange( from, to, spbrkpts, tpbrkpts );

    if( ! initialbin.isnonempty() ) {
	makeBorderTrim( from, to );
    } else {
	REAL rate[2];
	qlist->findRates( spbrkpts, tpbrkpts, rate );

    	if( decompose( initialbin, min(rate[0], rate[1]) ) ) 
	    mylongjmp( jumpbuffer, 31 );
    }

    backend.bgnsurf( renderhints.wiretris, renderhints.wirequads, nuid );
    subdivideInS( initialbin );
    backend.endsurf();
}