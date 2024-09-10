void MComponent::writeRule( ContFile& mak )
{
    if( !_target->ismakeable() ) return;

    WFileName tgt;
    _target->absName( tgt );

    for( int i=0; i<_workFiles.count(); i++ ) {
        MWorkFile* w = (MWorkFile*)_workFiles[i];
        MItem* m = w->item();
        if( !m->isMask() && m->ismakeable() ) {
            WFileName r;
            m->absResult( r );
            if( r.needQuotes() ) {
                r.addQuotes();
            }
            if( w->needQuotes() ) {
                w->addQuotes();
            }
            mak.printf( "%s : %s", (const char*)r, (const char*)*w );
            r.removeQuotes();
            w->removeQuotes();
            if( _autodepend ) mak.puts( " .AUTODEPEND" );
            mak.puts( "\n" );
            WString c;
            w->makeCommand( c, NULL );
            writeTargetCD( mak );
            mak.puts( c );
            mak.puts( "\n" );
            w->puts( r );       //setup for later use by target-maker
        }
    }
    if( tgt.needQuotes() ) {
        tgt.addQuotes();
    }
    mak.printf( "%s :", (const char*)tgt );
    tgt.removeQuotes();
    int jcount = _workFiles.count();
    for( int j=0; j<jcount; j++ ) {
        MWorkFile* w = (MWorkFile*)_workFiles[j];
        if( !w->isMask() ) {
            if( w->needQuotes() ) {
                w->addQuotes();
            }
            mak.printf( " %s", (const char*)*w );
            w->removeQuotes();
            w->relativeTo( _filename );
        }
    }
    if( _autodepend ) mak.puts( " .AUTODEPEND" );
    mak.puts( "\n" );
    bool browseable = writeCBR();
    if( _target->ismakeable() ) {
        WFileName fn; _target->absName( fn );
        MWorkFile w( fn, _mode, _target, this );
        WString c;
        if( browseable && _config->browseMerge().size() > 0 ) {
            MCommand cmd;
            cmd.concatf( " %s @$*.cbr", (const char*)_config->browseMerge() );
            expand( c, cmd );
        }
        expand( c, _before );
        w.makeCommand( c, &_workFiles );
        expand( c, _after );
        writeTargetCD( mak );
        mak.puts( c );
        mak.puts( "\n" );
    }
}