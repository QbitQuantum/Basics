void QLiveGUI::init( ci::Rectf rect )   // rect doesn't make any f*****g sense! TODO: remove this shit!
{
    std::vector<QLiveTrackRef> tracks = mLive->getTracks();
    
    if ( tracks.empty() )
        return;
    
    int margin  = 15;
    
    int n = 0;
    for( auto k=0; k < tracks.size(); k++ )
        if ( !boost::starts_with( tracks[k]->getName(), "_") )          // IGNORE all the params in the tracks that starts with "_"
            n++;
    
    Vec2f size;
    size.x = ( rect.getWidth() - ( n + 1 ) * margin ) / n;
    size.y = 150;
    for( auto k=0; k < tracks.size(); k++ )
    {
        if ( boost::starts_with( tracks[k]->getName(), "_") )          // IGNORE all the params in the tracks that starts with "_"
            continue;
        
        mControls.push_back( QLiveGuiTrackControl::create( mLive, tracks[k], size, mCanvas ) );
    }
}