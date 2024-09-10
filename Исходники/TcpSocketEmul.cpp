 // ---------------------------------------------------
 // implement ITcpSocket
 void TcpSocketEmul::LinkUserToSocket(Utils::SafeRef<iNet::ITcpSocketToUser> iTcpSocketToUser) 
 {
     ESS_ASSERT(!iTcpSocketToUser.IsEmpty());
     m_pOwner = iTcpSocketToUser;
 }