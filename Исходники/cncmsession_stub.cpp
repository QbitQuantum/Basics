#include <es_sock_partner.h>

#include "cncmsession.h"
#include "cncmstream.h"
#include "cncmconnection.h"
#include "cncmconnectionobserverhandler.h"
#include "cncmlocaladdressresolver.h"
//#include "cncmicmpreceiver.h"
#include "ncmconnectionmultiplexerlogs.h"
//#include "cncmportstore.h"
#include "mncmsessionobserver.h"
#include "mncmconnectionmultiplexerobserver.h"

const TUint KESockMessageSlots = 16;

const TUint32 KLocalAddress = INET_ADDR( 10, 168, 0, 100 );
const TUint KLocalPort = 5000;

// ---------------------------------------------------------------------------
// CNcmSessionSession::CNcmSession
// ---------------------------------------------------------------------------
//
CNcmSession::CNcmSession( TUint aSessionId,
    TUint32 aIapId,
    MNcmConnectionMultiplexerObserver& aObserver,
    MNcmSessionObserver& aSessionObserver ) :
    CActive( EPriorityStandard ),
    iSessionId( aSessionId ), iIapId( aIapId ), iObserver( aObserver ),
    iSessionObserver( aSessionObserver )
    {
    CActiveScheduler::Add( this );