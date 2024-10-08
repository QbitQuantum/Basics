DWORD WindowsServicePrincipalName::dsMakeSpn(DWORD* length, wchar_t* value) {
    DWORD status;

#ifdef UNICODE
    SWIFT_LOG(debug) << "UNICODE is defined" << std::endl;
#else
    SWIFT_LOG(debug) << "UNICODE is not defined" << std::endl;
#endif

    SWIFT_LOG(debug) << "serviceClass_: " << convertWStringToString(serviceClass_.c_str()) << std::endl;
    SWIFT_LOG(debug) << "serviceName_: " << convertWStringToString(serviceName_.c_str()) << std::endl;
    SWIFT_LOG(debug) << "instanceName_: " << convertWStringToString(instanceName_.c_str()) << std::endl;
    SWIFT_LOG(debug) << "referrer_: " << convertWStringToString(referrer_.c_str()) << std::endl;
    SWIFT_LOG(debug) << "instancePort_: " << instancePort_ << std::endl;
    SWIFT_LOG(debug) << "length: " << *length << std::endl;

    /* Call the Unicode function because that is recommended:
https://msdn.microsoft.com/en-us/library/windows/desktop/ff381407%28v=vs.85%29.aspx */
    status =  DsMakeSpnW(
            serviceClass_.c_str(),
            serviceName_.c_str(),
            instanceName_.empty() ? NULL : instanceName_.c_str(),
            instancePort_,
            referrer_.empty() ? NULL : referrer_.c_str(),
            length,
            value);
    if (status != ERROR_SUCCESS) {
        boost::system::error_code errorCode(status, boost::system::system_category());

        SWIFT_LOG(debug) << std::hex << "status: 0x" << status << ": " << errorCode.message() << std::endl;
    }

    return status;
}