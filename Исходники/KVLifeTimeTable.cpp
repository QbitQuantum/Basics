//_____________________________________________
void KVLifeTimeTable::Initialize()
{

    TString dfile;
    dfile.Form("%s.DataFile",GetName());
    TString cl_path;
    if( !KVBase::SearchKVFile(gEnv->GetValue(dfile.Data(),""),cl_path,"data") ) {
        Error("Initialize","No file found for %s",GetName());
        return;
    }
    else {
        //Info("Initialize","%s will be read",gEnv->GetValue(dfile.Data(),""));
    }
    SetTitle(gEnv->GetValue(dfile.Data(),""));

    Int_t ntot=0;
    nucMap = new TMap(50,2);
    KVFileReader* fr = new KVFileReader();
    fr->OpenFileToRead(cl_path.Data());

    //Premier passage
    while (fr->IsOK()) {

        fr->ReadLine(" ");
        if (fr->GetNparRead()==0) break;
        else if (fr->GetReadPar(0).BeginsWith("//")) {

            kcomments+=fr->GetCurrentLine();
            kcomments+="\n";

        }
        else {
            Int_t zz = fr->GetIntReadPar(0);
            Int_t aa = fr->GetIntReadPar(1);
            GiveIndexToNucleus(zz,aa,ntot);
            ntot+=1;
        }
    }

    if ( !fr->PreparForReadingAgain() ) return;

    //Info("Initialize","Set up map for %d nuclei", ntot);
    CreateTable(ntot);

    KVLifeTime* lf = 0;
    ntot=0;
    while (fr->IsOK()) {

        fr->ReadLine(" ");
        if (fr->GetCurrentLine().IsNull()) {
            break;
        }
        else if (fr->GetNparRead()==0) {
            break;
        }
        else if (fr->GetReadPar(0).BeginsWith("//")) { }
        else {
            Double_t val = fr->GetDoubleReadPar(2);

            CreateElement(ntot);
            lf = (KVLifeTime* )GetCurrent();

            if (fr->GetNparRead()>3) {
                TString unit = fr->GetReadPar(3);
                if ( unit.EndsWith("eV") ) {
                    lf->SetResonnance(kTRUE);
                    val *= ToMeV(unit);
                }
                else {
                    lf->SetResonnance(kFALSE);
                    val *= ToSecond(unit);
                }
                if (fr->GetNparRead()>4) {
                    Int_t meas = fr->GetReadPar(4).Atoi();
                    lf->SetMeasured(meas);
                }
                else {
                    if (ntot==0) InfoOnMeasured();
                }
            }
            lf->SetValue(val);

            ntot+=1;
        }

    }

    //Info("Initialize","table initialised correctly for %d nuclei", ntot);
    fr->CloseFile();
    delete fr;

}