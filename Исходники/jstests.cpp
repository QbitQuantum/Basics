 void run() {
     client.insert( ns(), BSON( "i" << 1 ) );
     BSONObj obj = client.findOne( ns(), BSONObj() );
     client.remove( ns(), BSONObj() );
     client.insert( ns(), BSON( "r" << BSON( "$ref" << "jstests.informaldbref" << "$id" << obj["_id"].__oid() << "foo" << "bar" ) ) );
     obj = client.findOne( ns(), BSONObj() );
     ASSERT_EQUALS( "bar", obj[ "r" ].embeddedObject()[ "foo" ].str() );
     
     ASSERT( client.eval( "unittest", "x = db.jstests.informaldbref.findOne(); y = { r:x.r }; db.jstests.informaldbref.drop(); y.r[ \"a\" ] = \"b\"; db.jstests.informaldbref.save( y );" ) );
     obj = client.findOne( ns(), BSONObj() );
     ASSERT_EQUALS( "bar", obj[ "r" ].embeddedObject()[ "foo" ].str() );            
     ASSERT_EQUALS( "b", obj[ "r" ].embeddedObject()[ "a" ].str() );            
 }