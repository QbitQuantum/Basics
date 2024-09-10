void TextEdit::onMouseDown(const Event &event)
{
   dragHit = false;

   //undo any block function
   blockStart = 0;
   blockEnd = 0;

   //find out where the cursor should be
   int pos = setCursorPos(event.ptMouse);

   //if the position is to the left
   if (pos == -1) cursorPos = 0;
   //else if the position is to the right
   else if (pos == -2) cursorPos = strlen(text);
   //else set the cursorPos
   else cursorPos = pos;

   //save the mouseDragPos
   mouseDragStart = cursorPos;

   //lock the mouse
   mouseLock();

   //set the drag var
   dragHit = TRUE;
   
   //let the parent get the event
   Parent::onMouseDown(event);
}