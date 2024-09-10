Int
getUndoTextBuffer(TextBuffer tb)
{   long caret = -1;

    if ( tb->undo_buffer != NULL )
    {   UndoBuffer ub = tb->undo_buffer;
        UndoCell cell;

        if ( (cell = ub->current) == NULL )	/* No further undo's */
            fail;

        while(cell != NULL)
        {   DEBUG(NAME_undo, Cprintf("Undo using cell %d: ",
                                     Distance(cell, ub->buffer)));
            switch( cell->type )
            {
            case UNDO_DELETE:
            {   UndoDelete d = (UndoDelete) cell;
                string s;

                s.size = d->len;
                s.iswide = d->iswide;
                if ( d->iswide )
                    s.s_textA = d->text.A;
                else
                    s.s_textW = d->text.W;

                DEBUG(NAME_undo, Cprintf("Undo delete at %ld, len=%ld\n",
                                         d->where, d->len));
                insert_textbuffer(tb, d->where, 1, &s);
                caret = max(caret, d->where + d->len);
                break;
            }
            case UNDO_INSERT:
            {   UndoInsert i = (UndoInsert) cell;
                DEBUG(NAME_undo, Cprintf("Undo insert at %ld, len=%ld\n",
                                         i->where, i->len));
                delete_textbuffer(tb, i->where, i->len);
                caret = max(caret, i->where);
                break;
            }
            case UNDO_CHANGE:
            {   UndoChange c = (UndoChange) cell;
                string s;

                s.size = c->len;
                s.iswide = c->iswide;
                if ( c->iswide )
                    s.s_textA = c->text.A;
                else
                    s.s_textW = c->text.W;

                DEBUG(NAME_undo, Cprintf("Undo change at %ld, len=%ld\n",
                                         c->where, c->len));

                change_textbuffer(tb, c->where, &s);
                caret = max(caret, c->where + c->len);
                break;
            }
            }

            cell = cell->previous;
            if ( cell == NULL || cell->marked == TRUE )
            {   ub->current = cell;

                if ( cell == ub->checkpoint )	/* reached non-modified checkpoint */
                {   DEBUG(NAME_undo, Cprintf("Reset modified to @off\n"));
                    CmodifiedTextBuffer(tb, OFF);
                }

                changedTextBuffer(tb);
                ub->undone = TRUE;

                answer(toInt(caret));
            }
        }
    }

    fail;
}