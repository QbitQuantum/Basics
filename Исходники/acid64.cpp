 SafeThreadToFibre (LPVOID &fiber)
     :m_converted(false)
     ,m_fiber(fiber)
 {
     fiber = GetCurrentFiber ();
     if ((fiber == 0) || (fiber == (LPVOID)0x1E00/*see boost*/))
     {
         fiber = ConvertThreadToFiber (NULL);
         if (!fiber)
             throw 0;
         m_converted = true;
     }
 }