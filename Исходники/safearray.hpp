    safearray_t( SAFEARRAY *& p ) : psa_( p ), pdata_(0), size_(0) {
        SafeArrayAccessData( psa_, reinterpret_cast<void **>(&pdata_) );
		LONG lBound, uBound;
		SafeArrayGetLBound( psa_, 1, &lBound );
		SafeArrayGetUBound( psa_, 1, &uBound );
		size_ = uBound - lBound + 1;
    }