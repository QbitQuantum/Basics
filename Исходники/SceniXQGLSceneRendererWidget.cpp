        void SceniXQGLSceneRendererWidget::setContinuousUpdate( bool onOff )
        {
          if( onOff != m_continuousUpdate )
          {
            m_continuousUpdate = onOff;
            if( onOff )
            {
              // arg of 0 means signal every time there are no more window events to process
              m_timerID = startTimer(0);
            }
            else
            {
              DP_ASSERT( m_timerID != -1 );

              killTimer( m_timerID );
              m_timerID = -1;
            }
          }
        }