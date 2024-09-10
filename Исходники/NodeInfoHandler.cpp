 void NodeInfoHandler::OnDeleteRequest(const Safir::Dob::EntityRequestProxy /*entityRequestProxy*/,
                                       Safir::Dob::ResponseSenderPtr    responseSender)
 {
     responseSender->Send(Safir::Dob::ErrorResponse::CreateErrorResponse
                          (Safir::Dob::ResponseGeneralErrorCodes::SafirReqErr(),
                           L"It is not possible to send delete requests on Safir::Dob::NodeStatus"));
 }