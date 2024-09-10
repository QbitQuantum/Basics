void DopeApp::OnDeleteRequest(const Safir::Dob::EntityRequestProxy entityRequestProxy,
                              Safir::Dob::ResponseSenderPtr        responseSender)
{ 
    responseSender->Send(Safir::Dob::ErrorResponse::Create()); 
};