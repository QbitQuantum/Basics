//-------------------------------------------------------------------------------------------------------------------
TEST_F(SocketTest, TcpConnect)
{
	Socket skts ;
	Socket sktc ;

	// client
	EXPECT_FALSE(sktc.clientConnect(TCP_SKTNAME)) ;

	// server
//	EXPECT_TRUE(skts.serverListen("*:3333")) ;
	EXPECT_TRUE(skts.serverListen(TCP_SKTNAME)) ;

	// client
	EXPECT_TRUE(sktc.clientConnect(TCP_SKTNAME)) ;

	sktc.close() ;
	skts.close() ;
}