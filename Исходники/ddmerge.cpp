//------------------------------------------------------------------------------------
int main(int argc, char **argv)
{
try {
   int i,n;
   string line,line2,id,rawfile,ddrfile,outfile,site1,site2,sat1,sat2;
   ifstream instr;
   ofstream outstr;
   Epoch CurrEpoch;

   clock_t totaltime = clock();
      // print title and current time to screen
   CurrEpoch.setLocalTime();
   cout << "ddmerge version " << Version << " run " << CurrEpoch << endl;

   if(argc < 4) {
      cout << "Usage: ddmerge <RAWfile> <DDRfile> <output_file>" << endl;
      cout << "    where the two input file are output of DDBase" << endl;
      cout << " ddmerge will take elevation and azimuth data from the RAW" << endl;
      cout << " file and append it to the appropriate line in the DDR file" << endl;
      cout << " and output to the output file" << endl;
      return -1;
   }
   rawfile = string(argv[1]);
   ddrfile = string(argv[2]);
   outfile = string(argv[3]);

      // this must be binary or you get the wrong answers.
   instr.open(rawfile.c_str(),ios::in|ios::binary);
   if(!instr.is_open()) {
      cout << "Failed to open input file " << rawfile << endl;
      return -1;
   }
   cout << "Opened input file " << rawfile << endl;
   instr.exceptions(fstream::failbit);

   n = 0;
   while(1) {
      try {
         //instr.read((char *)p2, 1); // get one char
         instr.getline(buffer,BUFF_SIZE);
      }
      catch(exception& e) {}
      if(instr.bad()) cout << "Read error" << endl;
      if(instr.eof()) { cout << "Reached EOF" << endl; break; }

      n++;
      line = string(buffer);
      stripTrailing(line,'\r');
      if(word(line,0) == "RAW") {
         id = word(line,1);
         if(id != "site") {
            id += " " + word(line,2);
            if(Chunklist.find(id) == Chunklist.end()) {
               Chunk newchunk;
               newchunk.filepos = instr.tellg();
               newchunk.line = line;
               Chunklist[id] = newchunk;
            }
         }
      }
   }

   instr.clear();
   instr.close();

   // you must use pointers to the streams because storing a stream inside an object
   // that goes into an STL container leads to weird errors...try it.
   filepointer = new ifstream[Chunklist.size()];
   if(!filepointer) { cout << "failed to allocate filepointers" << endl; return -1; }

   map<string,Chunk>::iterator it;
   for(i=0,it=Chunklist.begin(); it != Chunklist.end(); i++,it++) {
      filepointer[i].open(rawfile.c_str(), ios::in|ios::binary);
      if(!filepointer[i].is_open()) {
         cout << "Failed to open chunk " << i << endl;
         break;
      }
      filepointer[i].exceptions(fstream::failbit);
      it->second.fpindex = i;
      filepointer[i].seekg(it->second.filepos);
   }

   outstr.open(outfile.c_str(), ios::out);
   if(!outstr.is_open()) {
      cout << "Failed to open output file " << outfile << endl;
      return -1;
   }
   cout << "Opened output file " << outfile << endl;
   outstr.exceptions(fstream::failbit);

   //for(it=Chunklist.begin(); it != Chunklist.end(); it++) {
   //   if(! it->second.status) continue;
   //   outstr << "Chunk " << it->first << endl;
   //   outstr << it->second.Update() << endl;
   //   outstr << it->second.Update() << endl;
   //   outstr << endl;
   //}

   instr.open(ddrfile.c_str());
   if(!instr.is_open()) {
      cout << "Failed to open input file " << ddrfile << endl;
      return -1;
   }
   cout << "Opened input file " << ddrfile << endl;
   instr.exceptions(fstream::failbit);

   n = 0;
   while(1) {
      try { instr.getline(buffer,BUFF_SIZE); }
      catch(exception& e) {} //cout << "exception: " << e.what() << endl;
      if(instr.bad()) { cout << "Read error" << endl; break; }
      if(instr.eof()) { cout << "Reached EOF" << endl; break; }

      n++;
      line = string(buffer);
      stripTrailing(line,'\r');
      if(word(line,0) == "RES") {
         site1 = word(line,1);
         if(site1 != "site") {
            site2 = word(line,2);
            sat1 = word(line,3);
            sat2 = word(line,4);
            id = word(line,7);        // TD different for MJD
            n = asInt(id);
            outstr << line;                          // endl below
            // find the corresponding lines in the chunks
            id = site1 + " " + sat1;
            line2 = Chunklist[id].find(n);
            if(Chunklist[id].status) outstr
               << " " << rightJustify(word(line2,11),5)
               << " " << rightJustify(word(line2,12),6);
            id = site1 + " " + sat2;
            line2 = Chunklist[id].find(n);
            if(Chunklist[id].status) outstr
               << " " << rightJustify(word(line2,11),5)
               << " " << rightJustify(word(line2,12),6);
            id = site2 + " " + sat1;
            line2 = Chunklist[id].find(n);
            if(Chunklist[id].status) outstr
               << " " << rightJustify(word(line2,11),5)
               << " " << rightJustify(word(line2,12),6);
            id = site2 + " " + sat2;
            line2 = Chunklist[id].find(n);
            if(Chunklist[id].status) outstr
               << " " << rightJustify(word(line2,11),5)
               << " " << rightJustify(word(line2,12),6);
         }
         else outstr
            << line << "  EL11   AZ11  EL12   AZ12  EL21   AZ21  EL22   AZ22";
      }
      else outstr << line << endl
         << "# ddmerge (v." << Version << ") " << rawfile
         << " " << ddrfile << " " << outfile << " Run " << CurrEpoch;
      outstr << endl;
   }

   instr.close();
   delete[] filepointer;

      // compute run time
   totaltime = clock()-totaltime;
   cout << "ddmerge timing: " << fixed << setprecision(3)
      << double(totaltime)/double(CLOCKS_PER_SEC) << " seconds." << endl;

   return 0;
}
catch(Exception& e) {
   cout << "GPSTk Exception : " << e;
}
catch (...) {
   cout << "Unknown error in ddmerge.  Abort." << endl;
}

      // close files
   return -1;
}   // end main()