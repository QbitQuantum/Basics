/// Load main file
void TPgBlob::LoadMain() {
    TFIn SIn(FNm + ".main");
    TInt children_cnt;
    children_cnt.Load(SIn);
    Fsm.Load(SIn);
    Files.Clr();
    for (int i = 0; i < children_cnt; i++) {
        TStr FNmChild = FNm + ".bin" + TStr::GetNrNumFExt(i);
        Files.Add(TPgBlobFile::New(FNmChild, Access, MxBlobFLen));
    }
}