void DecodeRunlist(const TString &val){
        //
        // Tokenize run list
        //
        TObjArray *runstrings = val.Tokenize(",");
        TObjString *os;
        TString runstr;
        TIter runIter(runstrings);
        g_runlist.Set(runstrings->GetEntries());
        int nruns(0);
        while((os = dynamic_cast<TObjString *>(runIter()))){
                runstr = os->String();
                g_runlist[nruns++] = runstr.Atoi();
        }
        delete runstrings;
}