/// Copies the element into the provided UtlString
bool  CallStateEventBuilder_XML::finishElement(UtlString& event)
/**<
 * @returns
 * - true if the returned element is validly constructed
 * - false if not (a caller error)
 */
{
   bool isComplete = mEventComplete;
   event.remove(0);

   if (isComplete)
   {
      event.append(mCurrentEvent);
      event.append(mCallInfo);
      event.append(mLaterElement);
      event.append(mViaHeader);
      event.append(mEndElement);
      event.append(CallEventElementEnd);
      event.append('\n');

      reset();
   }

   return isComplete;
}