void Simulator::doAllEvents() {
	/*	Main driver of the simulation object, wherein it repeatedly removes the
		first event from the OrderedSet, updates virtual time to the time of the event, and
		executes the event. This continues as long as there are events to procesS->			  	*/

	while (events.len() > 0) {							// As long as there are events in the OrderedSet...
		Event * E = events.removeFirst();				// ...Remove the first entry in the OrderedSet
		vtime_ = E->time();								// ...Set simulator time to the time of the event
		E->execute();									// ...Execute the event using that event's execute method.
	}
	
	sink();												// Dump stats
}