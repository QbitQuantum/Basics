 Section::~Section() {
     if( m_sectionIncluded ) {
         SectionEndInfo endInfo( m_info, m_assertions, m_timer.getElapsedSeconds() );
         if( uncaught_exceptions() )
             getResultCapture().sectionEndedEarly( endInfo );
         else
             getResultCapture().sectionEnded( endInfo );
     }
 }