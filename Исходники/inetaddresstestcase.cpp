        /**
         * Tests the InetAddress::getLocalHost() method.
         */
        void testGetLocalHost() {
           InetAddressPtr addr = InetAddress::getLocalHost();

           LOGUNIT_ASSERT(addr->getHostAddress() == LOG4CXX_STR("127.0.0.1"));
           LOGUNIT_ASSERT(!addr->getHostName().empty());
        }