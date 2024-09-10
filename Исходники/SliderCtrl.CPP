CCtrl *SliderNew()
{
  Bool old_preempt;
  CCtrl *c=CAlloc(sizeof(CCtrl));
  c->win_task=Fs;
  c->flags=CTRLF_SHOW|CTRLF_CAPTURE_LEFT_IP;
  c->type=CTRLT_GENERIC;
  c->state=&sld;
  MemSet(&sld,0,sizeof(CSliderState));
  c->draw_it=&DrawSliderCtrl;
  c->left_click=&LeftClickSlider;
  c->update_derived_vals=&UpdateDerivedSliderCtrl;
  old_preempt=Preempt(OFF);
  QueIns(c,Fs->last_ctrl);
  TaskDerivedValsUpdate;
  Preempt(old_preempt);
  return c;
}