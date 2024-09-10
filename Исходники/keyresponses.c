// Note this function is RECURSIVE.
// deletes the object before the cursor. If the measure is empty it moves to the end of the previous measure and calls itself.
// after deleting an object it backs-up on any rhythm pattern being followed.
void
deletepreviousobject (GtkAction* action, DenemoScriptParam *param)
{

  /* remove the object preceding the cursor, within the current measure */
  if (Denemo.project->movement->cursor_x)
    {
      /* Then move the cursor back */
      movecursorleft (NULL, NULL);
      DenemoObject *curObj = (DenemoObject*)Denemo.project->movement->currentobject->data;
      gboolean anote = (curObj->type == CHORD) && ((chord*)curObj->object)->notes;
      /* And delete */
      deleteobject (NULL, NULL);
      /* if you are following a rhythmic pattern then backup the pattern */
      if ((Denemo.project->mode & (INPUTEDIT) && Denemo.project->rstep))
        {
          if (anote)
            Denemo.project->rstep = Denemo.project->rstep->prev;          /* rstep list of elements is circular */
          if (Denemo.project->cstep)
            {
              RhythmPattern *cursnip = (RhythmPattern *)Denemo.project->currhythm->data;
              Denemo.project->cstep = Denemo.project->cstep->prev ? Denemo.project->cstep->prev : g_list_last (Denemo.project->cstep);// cstep list of DenemoObjects is not circular
            }
          if (((RhythmElement *) Denemo.project->rstep->data)->highlightlabel)
            {
                RhythmPattern *cursnip = (RhythmPattern *)Denemo.project->currhythm->data;
                set_rhythm_label (cursnip, ((RhythmElement *) Denemo.project->rstep->data)->highlightlabel);
            }
        }

    }
  else
    {                           /* go to the previous measure, go to end of it, and start deleting there */
      if (Denemo.project->movement->currentmeasure->prev)
        {
          DenemoScriptParam param;

          do
            {
              movetomeasureleft (NULL, &param);
              //go to end
              while (Denemo.project->movement->currentobject && (Denemo.project->movement->currentobject->next))
                {
                  Denemo.project->movement->currentobject = Denemo.project->movement->currentobject->next;
                  Denemo.project->movement->cursor_x++;
                }
            }
          while (param.status && !Denemo.project->movement->currentobject);


          if (Denemo.project->movement->currentobject)
            {
              movecursorright (NULL, NULL);
              deletepreviousobject (NULL, NULL);//RECURSIVE!!
            }
        }
    }
}