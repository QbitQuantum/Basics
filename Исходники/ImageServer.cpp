ImageServer::~ImageServer()
{
  CosNaming::Name n;
  n.length(1);
  n[0].id = CORBA::string_dup("Image");
  namingContext->unbind(n);
}