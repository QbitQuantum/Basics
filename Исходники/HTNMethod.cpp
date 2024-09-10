void HTNMethod::parseTaskList( Filereader & f, TokenStruct< std::string > & ts, Domain & d ) {
f.next();
f.assert( "(" );
for ( f.next(); f.getChar() != ')'; f.next() ) {
		f.assert( "(" );
		std::string s = f.getToken();

		Task * task = new Task(s);
		task->SHOPparse( f, ts, d );
		tasks.push_back( task );
		d.tasks.insert( task );
	}
	++f.c;
f.next();
f.assert( ")" );
}