public CTaskSettings *SettingsPush(CTask *task=NULL,I64 flags=0)
{ //This is typically used at the start of an application.
  //It saves many settings so they can be restored
  //at the end of the application with $LK,"SettingsPop","MN:SettingsPop"$().

  CTaskSettings *tempse;
  CDoc *doc;
  if (!task) task=Fs;
  if (!TaskValidate(task)) return NULL;
  tempse=CAlloc(sizeof(CTaskSettings),task);
  tempse->draw_it=task->draw_it;
  GetVGAPalette4(tempse->palette4);
  tempse->task_end_cb=task->task_end_cb;

  if (!(flags&TSF_SAME_SONG)) {
    if (tempse->song_task=task->song_task) {
      Suspend(task->song_task);
      Snd(0);
    }
    task->song_task=NULL;
  }

  if (tempse->animate_task=task->animate_task)
    Suspend(task->animate_task);
  task->animate_task=NULL;

  if (doc=DocPut(task)) {
    tempse->cursor=!Bt(&doc->flags,DOCf_HIDE_CURSOR);
    tempse->scroll=!Bt(&doc->flags,DOCf_NO_SCROLL_BARS);
  }

  tempse->left=task->win_left;
  tempse->right=task->win_right;
  tempse->top=task->win_top;
  tempse->bottom=task->win_bottom;

  tempse->scroll_x=task->win_scroll_x;
  tempse->scroll_y=task->win_scroll_y;
  tempse->scroll_z=task->win_scroll_z;

  tempse->win_inhibit=task->win_inhibit;
  MemCpy(&tempse->snap,&task->snap,sizeof(CSnap));

  tempse->win_max_refresh=task->win_max_refresh;
  tempse->text_attr=task->text_attr;
  StrCpy(tempse->task_title,task->task_title);
  tempse->title_src  =task->title_src;
  tempse->border_attr=task->border_attr;
  tempse->border_src =task->border_src;
  tempse->border=!Bt(&task->display_flags,DISPLAYf_NO_BORDER);
  tempse->preempt=Bt(&task->task_flags,TASKf_PREEMPT);
  if (TaskValidate(ws_task))
    tempse->wordstat=TRUE;
  else
    tempse->wordstat=FALSE;

  tempse->next=task->next_settings;
  task->next_settings=tempse;
  return tempse;
}