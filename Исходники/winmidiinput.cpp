 void close() {
     MMRESULT res;
     if (m_handle != 0) {
         res = midiInReset( m_handle );
         if (res != MMSYSERR_NOERROR)
             qDebug() << "midiInReset() err:" << mmErrorString(res);
         res = midiInClose( m_handle );
         if (res != MMSYSERR_NOERROR)
             qDebug() << "midiInClose() err:" << mmErrorString(res);
         m_handle = 0;
     }
     m_currentInput.clear();
 }