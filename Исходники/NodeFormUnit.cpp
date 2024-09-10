void __fastcall TNodeForm::ChatButtonClick(TObject *Sender)
{
    char    str[512];
    char    name[128];
    int     i;
    node_t  node;

    for(i=0;i<ListBox->Items->Count;i++)
    	if(ListBox->Selected[i]==true) {
        	if(getnodedat(i+1,&node,NULL))
                break;
            if(node.status==NODE_WFC || node.status>NODE_QUIET)
                continue;
            sprintf(str,"%sCHAT %s %s %d %s"
                ,MainForm->cfg.exec_dir
                ,MainForm->cfg.ctrl_dir
                ,MainForm->cfg.node_path[i]
                ,i+1
                ,username(node.useron,name)
                );
            WinExec(str,SW_SHOWNORMAL);
        }
    TimerTick(Sender);
}