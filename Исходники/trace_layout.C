// Called when the stream of observations has finished to allow the implementor to perform clean-up tasks.
// This method is optional.
void externalTraceProcessor_File::obsFinished() {
  //cout << "externalTraceProcessor_File::obsFinished() finished="<<finished<<endl;
  // Only perform finishing code if we haven't already finished
  if(finished) return;
  finished = true;
  
  // We're done writing the trace file, so close the stream
  traceFile.close();
  
  // Execute the processing application
  ostringstream s; 
  s << processorFName;
  for(list<string>::iterator b=beforeParams.begin(); b!=beforeParams.end(); b++) s << " \""<<*b<<"\"";
  s << " \""<<obsFName<<"\"";
  for(list<string>::iterator a=afterParams.begin(); a!=afterParams.end(); a++) s << " \""<<*a<<"\"";
  //cout << "Command = "<<s.str()<<endl;

  // In case the processor executable is linked with Sight, unset the mutex environment variables from 
  // LoadTimeRegistry to make sure that they don't leak to the layout process
  common::LoadTimeRegistry::liftMutexes();
  
  FILE* out = popen(s.str().c_str(), "r");
  if(out == NULL) { cerr << "Failed to run command \""<<s.str()<<"\"!"<<endl; assert(0); }
  
  // Restore the LoadTimeRegistry mutexes
  common::LoadTimeRegistry::restoreMutexes();

  // Read out the trace produced by the processor
  char line[10000];
  while(fgets(line, 10000, out)) {
    //cout << "line=\""<<line<<"\""<<endl;
    // Split the line into its individual terms
    sight::common::escapedStr es(string(line), " ", sight::common::escapedStr::escaped);
    vector<string> terms = es.unescapeSplit(" ");

    map<string, string> ctxt, obs;
    map<string, anchor> obsAnchor;

    // Iterate over each term of this observation, adding each one into this observation's context, trace observation or anchors
    for(vector<string>::iterator t=terms.begin(); t!=terms.end(); t++) {
      //cout << "t=\""<<*t<<"\""<<endl;
      
      // Split the term into the key and the value
      sight::common::escapedStr es(string(*t), ":", sight::common::escapedStr::escaped);
      vector<string> kv = es.unescapeSplit(":");
      assert(kv.size()==3);
      string type=kv[0];
      string key =kv[1];
      string val =kv[2];

      // Identify the type of this term
      if(type == "ctxt") ctxt[key] = val;
      else if(type=="obs") obs[key] = val;
      else obsAnchor[key] = anchor(attrValue::parseInt(val));
    }
    
    // Emit the observation
    /*cout << "ctxt="<<endl;
    for(map<string, string>::iterator c=ctxt.begin(); c!=ctxt.end(); c++)
      cout << "    "<<c->first<<" => "<<c->second<<endl;*/
    emitObservation(-1, ctxt, obs, obsAnchor);
  }
  //cout << "done"<<endl;
  pclose(out);

  // Delete the file that was provided as input to the command since it is no longer needed
  unlink(obsFName.c_str());
  
  // Inform this trace's observers that it has finished
  traceObserver::obsFinished();
}