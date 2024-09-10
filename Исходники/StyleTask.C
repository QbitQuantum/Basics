void
StyleTask::markup( const Token &t )
{
  ComplexTask::markup(t);

   if (t.type() == START) {
      /*
       * Process Stylesheet start tags...
       */

      switch(t.olaf()){
       case OLAF::Stylesheet:

	 if (f_base >= 0) {
	    throw
	       (Unexpected
		("illegal nested STYLESHEET architectural form"));
	 }

	 f_base = t.level();
#ifdef FISH_DEBUG
	 DBUG_PRINT("Style", ("Style level=`%d'\n", f_base));
#endif
	 break;

       case OLAF::Path:

	 if ( f_pathbuf != NULL ) {
	    delete f_pathbuf;
	 }

	 f_pathbuf = new FlexBuffer();
	 f_buffer = f_pathbuf;
	 f_dataMode = inPath;
	 break;

       case OLAF::Select:
	 f_buffer->writeStr( "[" );
	 f_select = t.level();
	 break;
	
       case OLAF::Online:

	 f_buffer = onlineSS;
	 // feature_depth->clear();

	 if ( f_pathbuf == NULL ) {
	    throw(Unexpected("no path available for online feature."));
	 }

	 report_position(f_buffer, t.file(), t.line());
	 
	 f_buffer->writeStr( f_pathbuf->GetBuffer() );
	 f_buffer->writeStr( "\n" );
	 write_tabs( f_buffer, feature_depth, '\t');
	 f_buffer->writeStr( "{\n" );
	 feature_depth->push(t.level());

	 break;

       case OLAF::Print:

	 f_buffer = printSS;
	 // feature_depth->clear();

	 if ( f_pathbuf == NULL ) {
	    throw(Unexpected("no path available for print feature."));
	 }

	 report_position(f_buffer, t.file(), t.line());
	 f_buffer->writeStr( f_pathbuf->GetBuffer() );
	 f_buffer->writeStr( "\n" );
	 write_tabs( f_buffer, feature_depth, '\t');
	 f_buffer->writeStr( "{\n" );
	 feature_depth->push( t.level() );

	 break;

       case OLAF::AutoNumber:

	 report_position(onlineSS, t.file(), t.line());
	 autonumber(onlineSS, t);

	 report_position(printSS, t.file(), t.line());
	 autonumber(printSS, t);
	 break;
	
       case OLAF::FeatureText:

	 report_position(f_buffer, t.file(), t.line());
	 write_tabs( f_buffer, feature_depth, '\t');
	 
	 f_buffer->writeStr( t.giName() );
	 f_buffer->writeStr( ": " );
	 f_dataMode = startContent;
	 break;


      case OLAF::AutoRef:
	 {
	   const AttributeRec *arec;
	   int id = SGMLName::intern("ID");
	   if((arec = t.LookupAttr(id))){

	     if(f_dataMode == inContent){
	       f_buffer->writeStr(" + ");
	     }
	     
	     f_buffer->writeStr(arec->getAttrValueString());
	     f_dataMode = inContent;
	   } /* else document is not conforming... sgmls will report error */
	 }
	 break;
			       
       case OLAF::Feature:

	 report_position(f_buffer, t.file(), t.line());
	 write_tabs( f_buffer, feature_depth, '\t');
	 
	 f_buffer->writeStr( t.giName() );
	 f_buffer->writeStr( ": " );

	 const AttributeRec *arec;
   
	 /*
	  * Is it an enumeration feature?
	  */
	 if((arec = t.LookupAttr(OLAF::OL_Choice))){

           /* OL_Choice can only be applied to NAME attributes, hence
	      we don't neet to worryabout "'s in the attribute value.
	      */
	   /* except TRUE and FALSE....*/

	   const char *val = arec->getAttrValueString();

	   int quotes = !isdigit(val[0])
	     && strcmp(val, "TRUE") != 0
	     && strcmp(val, "FALSE") != 0
	     && val[0] != '@';

	   if (quotes) f_buffer->writeStr("\"");
	   f_buffer->writeStr(val);
	   if (quotes) f_buffer->writeStr("\" ");

	 }else{
	   f_buffer->writeStr( " {\n" );

	   for (arec = t.GetFirstAttr();
		arec != NULL;
		arec = t.GetNextAttr( arec )) {
	     
	     if (( arec->getAttrValueString() != NULL ) &&
		 ( arec->getAttrName() != OLAF::OLIAS )) {
	       
	       write_tabs( f_buffer, feature_depth, '\t');
	       f_buffer->put('\t');

	       write_attr(f_buffer, arec);

	       f_buffer->writeStr( ",\n" );
	     }
	   }
	   feature_depth->push(t.level());
	 }
	
	 break;
      }
      
      /*
       * first time we see OL-ID="...", spawn an OL_Data to collect the id
       */
      if ((f_base >= 0) && (f_locator == NULL) &&
          (t.LookupAttr(OLAF::OL_id))) {

#ifdef FISH_DEBUG
         DBUG_PRINT("Style", ("spawning locator collection subtask\n"));
#endif
         f_locator = new OL_Data(t, OLAF::OL_id, REMOVE_SPACES);
         addSubTask( f_locator );

      }
   }

   else if (t.type() == END) {

      if (f_base > 0) {

	int topelement;
	if ( !feature_depth->empty() ) {
	  if ( (topelement = feature_depth->top()) ) {
	    if ( topelement == t.level() ) {
	      topelement = feature_depth->pop();
	      write_tabs( f_buffer, feature_depth, '\t');
	      
	      if(feature_depth->empty()){
		f_buffer->writeStr("}\n");
	      }
	      else {
		f_buffer->writeStr("},\n");
	      }

	    }else if ( topelement + 1 == t.level() ) {
	      /* need a new-line at end of FeatureText data */
	      f_buffer->writeStr(",\n");
	    }
	  }
	}
	  
	if (t.level() == f_base) {
	  /* found end of stylesheet... write out StyleSheet data */
#ifdef FISH_DEBUG
	  DBUG_PRINT("Style", ("found end of stylesheet write out StyleSheet data\n"));
#endif
	  write_record();
	  
	}
	else if(t.level() == f_select){
	  f_buffer->writeStr( "]" );
	  f_select = -1;
	}
      }
    }
}