void Context_Shutdown_wrapped(xn::Context& self) {

#ifdef _DEBUG
    PyCout << "Shutting down OpenNI.." << std::endl;
#endif
    self.Shutdown();

}