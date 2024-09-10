void NemoCalendarAgendaModel::doRefresh(bool reset)
{
    mKCal::ExtendedCalendar::Ptr calendar = NemoCalendarDb::calendar();

    QDate endDate = mEndDate.isValid()?mEndDate:mStartDate;

    mKCal::ExtendedCalendar::ExpandedIncidenceList newEvents =
        calendar->rawExpandedEvents(mStartDate, endDate, false, false, KDateTime::Spec(KDateTime::LocalZone));

    // Filter out excluded notebooks
    for (int ii = 0; ii < newEvents.count(); ++ii) {
        if (!NemoCalendarEventCache::instance()->mNotebooks.contains(NemoCalendarDb::calendar()->notebook(newEvents.at(ii).second))) {
            newEvents.remove(ii);
            --ii;
        }
    }

    qSort(newEvents.begin(), newEvents.end(), eventsLessThan);

    int oldEventCount = mEvents.count();

    if (reset) {
        beginResetModel();
        qDeleteAll(mEvents);
        mEvents.clear();
    }

    QList<NemoCalendarEventOccurrence *> events = mEvents;

    int newEventsCounter = 0;
    int eventsCounter = 0;

    int mEventsIndex = 0;

    while (newEventsCounter < newEvents.count() || eventsCounter < events.count()) {
        // Remove old events
        int removeCount = 0;
        while ((eventsCounter + removeCount) < events.count() &&
               (newEventsCounter >= newEvents.count() ||
                eventsLessThan(events.at(eventsCounter + removeCount)->expandedEvent(),
                               newEvents.at(newEventsCounter))))
            removeCount++;

        if (removeCount) {
            Q_ASSERT(false == reset);
            beginRemoveRows(QModelIndex(), mEventsIndex, mEventsIndex + removeCount - 1);
            mEvents.erase(mEvents.begin() + mEventsIndex, mEvents.begin() + mEventsIndex + removeCount);
            endRemoveRows();
            for (int ii = eventsCounter; ii < eventsCounter + removeCount; ++ii)
                delete events.at(ii);
            eventsCounter += removeCount;
        }

        // Skip matching events
        while (eventsCounter < events.count() && newEventsCounter < newEvents.count() &&
               eventsEqual(newEvents.at(newEventsCounter), events.at(eventsCounter)->expandedEvent())) {
            Q_ASSERT(false == reset);
            eventsCounter++;
            newEventsCounter++;
            mEventsIndex++;
        }

        // Insert new events
        int insertCount = 0;
        while ((newEventsCounter + insertCount) < newEvents.count() && 
               (eventsCounter >= events.count() ||
                eventsLessThan(newEvents.at(newEventsCounter + insertCount),
                               events.at(eventsCounter)->expandedEvent())))
            insertCount++;

        if (insertCount) {
            if (!reset) beginInsertRows(QModelIndex(), mEventsIndex, mEventsIndex + insertCount - 1);
            for (int ii = 0; ii < insertCount; ++ii) {
                NemoCalendarEventOccurrence *event = 
                    new NemoCalendarEventOccurrence(newEvents.at(newEventsCounter + ii));
                mEvents.insert(mEventsIndex++, event);
            }
            newEventsCounter += insertCount;
            if (!reset) endInsertRows();
        }
    }

    if (reset)
        endResetModel();

    if (oldEventCount != mEvents.count())
        emit countChanged();
}