BSONObj v8ToMongo( v8::Handle<v8::Object> o ){
    BSONObjBuilder b;

    v8::Handle<v8::String> idName = String::New( "_id" );
    if ( o->HasRealNamedProperty( idName ) ){
        v8ToMongoElement( b , idName , "_id" , o->Get( idName ) );
    }
    
    Local<v8::Array> names = o->GetPropertyNames();
    for ( unsigned int i=0; i<names->Length(); i++ ){
        v8::Local<v8::String> name = names->Get(v8::Integer::New(i) )->ToString();

        if ( o->GetPrototype()->IsObject() &&
             o->GetPrototype()->ToObject()->HasRealNamedProperty( name ) )
            continue;
        
        v8::Local<v8::Value> value = o->Get( name );
        
        const string sname = toSTLString( name );
        if ( sname == "_id" )
            continue;

        v8ToMongoElement( b , name , sname , value );
    }
    return b.obj();
}