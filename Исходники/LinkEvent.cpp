void LinkEvent::ReplaceLinkByLinkedEvents(gd::Project & project, EventsList & eventList, unsigned int indexOfTheEventInThisList)
{
    //Finding what to link to.
    const EventsList * eventsToInclude = NULL;
    gd::ExternalEvents * linkedExternalEvents = NULL;
    if ( project.HasExternalEventsNamed(GetTarget()) )
    {
        linkedExternalEvents = &project.GetExternalEvents(GetTarget());
        eventsToInclude = &project.GetExternalEvents(GetTarget()).GetEvents();
    }
    else if ( project.HasLayoutNamed(GetTarget()) ) eventsToInclude = &project.GetLayout(GetTarget()).GetEvents();

    if ( eventsToInclude != NULL )
    {
        unsigned int firstEvent = IncludeAllEvents() ? 0 : GetIncludeStart();
        unsigned int lastEvent = IncludeAllEvents() ? eventsToInclude->size() - 1 : GetIncludeEnd();

        //Check bounds
        if ( firstEvent >= eventsToInclude->size() )
        {
            std::cout << "Unable to get events from a link ( Invalid start )" << std::endl;
            linkWasInvalid = true;
            return;
        }
        if ( lastEvent >= eventsToInclude->size() )
        {
            std::cout << "Unable to get events from a link ( Invalid end )" << std::endl;
            linkWasInvalid = true;
            return;
        }
        if ( firstEvent > lastEvent )
        {
            std::cout << "Unable to get events from a link ( End is before start )" << std::endl;
            linkWasInvalid = true;
            return;
        }

        //Insert an empty event to replace the link event ( we'll delete the link event at the end )
        //( If we just erase the link event without adding a blank event to replace it,
        //the first event inserted by the link will not be preprocessed ( and it can be annoying if it require preprocessing, such as another link event ). )
        gd::EmptyEvent emptyEvent;
        eventList.InsertEvent(emptyEvent, indexOfTheEventInThisList);
        eventList.InsertEvents(*eventsToInclude, firstEvent, lastEvent, indexOfTheEventInThisList+1);

        //Delete the link event ( which is now at the end of the list of events we've just inserted )
        eventList.RemoveEvent(indexOfTheEventInThisList + 1 + static_cast<unsigned>(lastEvent-firstEvent)+1);
    }
    else
    {
        std::cout << "Unable to get events from a link." << std::endl;
        linkWasInvalid = true;

        //Delete the link event
        eventList.RemoveEvent(indexOfTheEventInThisList);
        return;
    }

    linkWasInvalid = false;
}