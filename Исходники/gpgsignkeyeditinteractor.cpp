unsigned int GpgSignKeyEditInteractor::nextState( unsigned int status, const char * args, Error & err ) const {
    d->started = true;
    using namespace GpgSignKeyEditInteractor_Private;
    static const Error GENERAL_ERROR = Error::fromCode( GPG_ERR_GENERAL );
    //static const Error INV_TIME_ERROR = Error::fromCode( GPG_ERR_INV_TIME );
    static const TransitionMap table( makeTable() );
    if ( needsNoResponse( status ) ) {
        return state();
    }

    using namespace GpgSignKeyEditInteractor_Private;

    //lookup transition in map
    const TransitionMap::const_iterator it = table.find( make_tuple( static_cast<SignKeyState>( state() ), status, std::string( args ) ) );
    if ( it != table.end() ) {
        return it->second;
    }

    //handle cases that cannot be handled via the map
    switch ( const unsigned int st = state() ) {
    case UIDS_ANSWER_SIGN_ALL:
        if ( status == GPGME_STATUS_GET_LINE &&
             strcmp( args, "keyedit.prompt" ) == 0 ) {
            if ( !d->signAll() ) {
                return UIDS_LIST_SEPARATELY;
            }
            err = Error::fromCode( GPG_ERR_UNUSABLE_PUBKEY );
            return ERROR;
        }
        break;
    default:
        if ( st >= UIDS_LIST_SEPARATELY && st < UIDS_LIST_SEPARATELY_DONE ) {
            if ( status == GPGME_STATUS_GET_LINE &&
                 strcmp( args, "keyedit.prompt" ) == 0 ) {
                return d->allUserIDsListed() ? UIDS_LIST_SEPARATELY_DONE : st+1 ;
            }
        }
        break;
    case CONFIRM:
    case ERROR:
        err = lastError();
        return ERROR;
    }

    err = GENERAL_ERROR;
    return ERROR;
}