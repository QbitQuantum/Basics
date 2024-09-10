void Win32Event::pulse() {
    if( isAvailable() ) {
        if( 0 == PulseEvent( event_ ) ) {
            PSS_THROW_PARAM1( ::pss::std::Win32Error(GetLastError()) , "");
        }
    } else {
        PSS_THROW_PARAM1( ::pss::std::Win32Error(constructError_) , "");
    }
}