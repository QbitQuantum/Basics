 void run() {
     // Exactly the same specs with the existing one, only
     // specified in a different order than the original.
     _client.insert("unittests.system.indexes",
             BSON("name" << "super2"
                  << "ns" << _ns
                  << "expireAfterSeconds" << 3600
                  << "sparse" << true
                  << "unique" << 1
                  << "dropDups" << true
                  << "key" << BSON("superIdx" << "2d")));
     ASSERT_EQUALS(_client.getLastError(), "");
 }