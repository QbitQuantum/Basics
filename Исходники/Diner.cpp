///////////////////
// Shutdown the diner
void Dnr_Shutdown(void)
{
    cDinerLayout.Shutdown();
    cDinerLayout2.Shutdown();

    if( psDiner ) {

        if( psDiner->pcLocation ) {
            psDiner->pcLocation->Shutdown();
            delete psDiner->pcLocation;
        }

        psDiner->cSky.Shutdown();

        delete psDiner;
    }

    psDiner = NULL;
}