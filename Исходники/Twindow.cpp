bool Twindow::TwidgetSubclassTbr::onEdit(void)
{
    int idff=self->getTbrIdff(id,bind);
    TffdshowParamInfo info;
    memset(&info,0,sizeof(info));
    if (self->deci->getParamInfo(idff,&info)!=S_OK) {
        return false;
    }
    int min,max,val;
    getEditMinMaxVal(info,&min,&max,&val);
    char_t valS[20];
    _itoa(val,valS,10);
    char_t query[100];
    tsprintf(query,self->_(0,_l("Enter value in range from %i to %i")),min,max);
    if (!self->inputString(self->_(0,_l("Edit trackbar value")),query,valS,20)) {
        return false;
    }
    storeEditValue(info,min,max,valS);
    return true;
}