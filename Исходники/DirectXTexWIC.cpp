 static inline HRESULT CreateMemoryStream( _Outptr_ IStream** stream )
 {
     auto randomAccessStream = ref new ::Windows::Storage::Streams::InMemoryRandomAccessStream();
     return CreateStreamOverRandomAccessStream( randomAccessStream, IID_PPV_ARGS( stream ) );
 }