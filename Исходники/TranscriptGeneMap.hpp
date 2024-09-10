 Index findTranscriptID( const std::string &tname ) {
     using std::distance;
     using std::lower_bound;
     auto it = lower_bound( _transcriptNames.begin(), _transcriptNames.end(), tname );
     return ( it == _transcriptNames.end() ) ? INVALID : ( distance(_transcriptNames.begin(), it) );
 }