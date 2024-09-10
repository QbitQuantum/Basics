  void	MIDITrack::Sort()
  {
//
// A simple single buffer sorting algorithm.
//
// first, see if we need sorting by checking each element
// with the next. they should all be in order.
//
// if not, do qsort algorithm
    
    unsigned int i;
    unsigned int first_out_of_order_item=0;
    
    for( i=0; i<num_events-1; ++i )
    {
      first_out_of_order_item=i+1;
      if( MIDITimedMessage::CompareEvents(
            *GetEventAddress(i),
            *GetEventAddress(first_out_of_order_item)
            )==1 )
        break;
    }
    
    if( first_out_of_order_item>=num_events-1 )
    {
//		return;		// no need for sort
    }
    
    QSort(0,num_events-1);
  }