void KIWAY::ExpressMail( FRAME_T aDestination,
                MAIL_T aCommand, const std::string& aPayload, wxWindow* aSource )
{
    KIWAY_EXPRESS   mail( aDestination, aCommand, aPayload, aSource );

    ProcessEvent( mail );
}