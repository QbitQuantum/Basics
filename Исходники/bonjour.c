void doregistration(const char *name, unsigned long port)
{    
    DNSServiceRegister(&service_ref, 0, 0, name, "_ftp._tcp.", NULL, NULL,
                       port, 0, NULL,
                       reg_reply,
                       NULL);
}