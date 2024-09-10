void i4_main(w32 argc, i4_const_str * argv)
{
#ifdef _WINDOWS
	set_unexpected(myUnexpectedExit);
#endif
	//golgotha_app app(argc, argv);
	g1_app=new golgotha_app(argc,argv);
	g1_app->run();
#ifdef _WINDOWS
	cwnd.Detach(); //Detach the MFC from the Main-Window, we are clearing up manually
#endif
	delete g1_app;
	g1_app=NULL;
}