/*
 * When a peer sends `auth: CAN' it asks for communication with another peer.
 * The other peer must send back `auth: OFC' to accept the connection.
 */
void auth_accept(int sockfd, const SA *peeraddr, socklen_t peeraddr_len)
{
    char auth_ofc[4 + strlen(AUTH_OFC) + 1];
    create_send_msg_static(AUTH_OFC, auth_ofc);

    Sendto(sockfd, auth_ofc, strlen(auth_ofc), 0, peeraddr, peeraddr_len);
}