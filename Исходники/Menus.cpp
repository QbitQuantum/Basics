void showgui(char *name)
{
    int pos = guistack.find(name);
    if(pos<0)
    {
        if(!guis.access(name)) return;
        if(guistack.empty()) menupos = menuinfrontofplayer();
        guistack.add(newstring(name));
    }
    else
    {
        pos = guistack.length()-pos-1;
        loopi(pos) delete[] guistack.pop();
    };
    menutab = 1;
    menustart = lastmillis;
};