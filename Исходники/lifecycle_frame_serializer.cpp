    template<> ACE_Message_Block *
    lifecycle_frame_serializer::pack( const LifeCycleData& v )
    {
	ACE_OutputCDR ace_cdr;
	OutputCDR cdr(ace_cdr);
	
	LifeCycleFrame frame( boost::apply_visitor( internal::lifecycle_command_visitor(), v ) );
	
	internal::lifecycle_serializer::serialize(cdr, frame);
	unsigned int size = boost::apply_visitor( internal::lifecycle_serializer_visitor(cdr), v );
	ACE_UNUSED_ARG(size);
	
	ACE_Message_Block * mb = cdr.begin()->clone();
	mb->length( cdr.length() );
	return mb;
    }