void finish_device_vocab( void )
{
    bool at_top_level;

    dev_vocab_control_struct_check();

    /*   We never remove the top-level device-node vocabulary,
     *       so we need to test whether we're about to.
     */

    at_top_level = BOOLVAL( current_device_node == &top_level_dev_node );
    if ( at_top_level )
    {
        tokenization_error( TKERROR,
	    "Encountered %s without corresponding NEW-DEVICE.  "
	    "Resetting definitions since start of tokenization.\n",
		statbuf );
    }else{    
	tokenization_error(INFO,
	    "Encountered %s.  Resetting definitions of device node",
		statbuf );
	started_at( current_device_node->ifile_name,
	     current_device_node->line_no );
    }

    /*  Now to business...   */
    delete_device_vocab();

    /*   Did we just get to the top-level device-node vocabulary
     *       when we weren't before?
     */
    if ( INVERSE(at_top_level) )
    {
	if ( current_device_node == &top_level_dev_node )
	{
	    tokenization_error(INFO,
		"Resuming definitions since start of tokenization.\n" );
	}else{
	    tokenization_error(INFO,
		"Resuming definitions of parent device-node" );
	    started_at( current_device_node->ifile_name,
		 current_device_node->line_no );
	}
    }
}