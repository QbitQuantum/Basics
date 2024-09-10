    virtual void CheckResult()
    {
        CPPUNIT_ASSERT_MESSAGE( "No events received", !m_events.empty() );

        const wxFileSystemWatcherEvent * const e = m_events.front();

        // this is our "reference event"
        const wxFileSystemWatcherEvent expected = ExpectedEvent();

        CPPUNIT_ASSERT_EQUAL( expected.GetChangeType(), e->GetChangeType() );

        CPPUNIT_ASSERT_EQUAL((int)wxEVT_FSWATCHER, e->GetEventType());

        // XXX this needs change
        CPPUNIT_ASSERT_EQUAL(wxEVT_CATEGORY_UNKNOWN, e->GetEventCategory());

        CPPUNIT_ASSERT_EQUAL(expected.GetPath(), e->GetPath());
        CPPUNIT_ASSERT_EQUAL(expected.GetNewPath(), e->GetNewPath());

        // Under MSW extra modification events are sometimes reported after a
        // rename and we just can't get rid of them, so ignore them in this
        // test if they do happen.
        if ( e->GetChangeType() == wxFSW_EVENT_RENAME &&
                m_events.size() == 2 )
        {
            const wxFileSystemWatcherEvent* const e2 = m_events.back();
            if ( e2->GetChangeType() == wxFSW_EVENT_MODIFY &&
                    e2->GetPath() == e->GetNewPath() )
            {
                // This is a modify event for the new file, ignore it.
                return;
            }
        }

        WX_ASSERT_EQUAL_MESSAGE
        (
            (
                "Extra events received, last one is of type %x, path=\"%s\" "
                "(the original event was for \"%s\" (\"%s\")",
                m_events.back()->GetChangeType(),
                m_events.back()->GetPath().GetFullPath(),
                e->GetPath().GetFullPath(),
                e->GetNewPath().GetFullPath()
            ),
            1, m_events.size()
        );

    }