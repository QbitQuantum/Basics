void
AmazonStore::addToCart()
{
    QString asin, name, price;
    int id = m_itemModel->idForIndex( m_selectedIndex );;

    // get item from collection
    if( m_itemModel->isAlbum( m_selectedIndex ) ) // album
    {
        Meta::AmazonAlbum* album;

        album = dynamic_cast<Meta::AmazonAlbum*>( m_collection->albumById( id ).data() );

        if( !album )
            return;

        name = m_collection->artistById( album->artistId() )->name() + " - " + album->name();
        asin = album->asin();
        price = album->price();
    }
    else // track
    {
        Meta::AmazonTrack* track;
        track = dynamic_cast<Meta::AmazonTrack*>( m_collection->trackById( id ).data() );

        if( !track )
            return;

        name = m_collection->artistById( track->artistId() )->name() + " - " + track->name();
        asin = track->asin();
        price = track->price();
    }

    AmazonShoppingCart::instance()->add( asin, price, name );
    m_checkoutButton->setEnabled( true );
}