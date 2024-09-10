bool
Compress( ClassAdCollectionServer *server, LocalCollectionQuery *query,
          const References &refs, CompressedAds &comp, list<ClassAd*> &rest )
{
    string                      key, sig;
    References::const_iterator  ritr;
    ClassAd                     *ad;
    CompressedAds::iterator     citr;
    ClassAdBin                  *bin;

    query->ToFirst( );
    query->Current( key );
    while( !query->IsAfterLast( ) ) {
        // get ad
        if( !( ad = server->GetClassAd( key ) ) ) {
            return( false );
        }

        // get signature of current ad
        if( !MakeSignature( ad, refs, sig ) ) {
            // can't make signature --- can't compress
            rest.push_back( (ClassAd*) ad->Copy( ) );
        }

        // get bin
        if( ( citr = comp.find( sig ) ) == comp.end( ) ) {
            // no bin ... make one
            bin = new ClassAdBin;
            bin->count = 1;

            // make a projected classad
            for( ritr=refs.begin( ); ritr!=refs.end( ); ritr++ ) {
                bin->ad->Insert( *ritr, ad->Lookup( *ritr )->Copy( ), false );
            }

            // insert bin into container
            comp[sig] = bin;
        } else {
            // increment membership in bin
            bin = citr->second;
            bin->count++;
        }

        // process next ad
        query->Next( key );
    }

    return( true );
}