void
TextComposition::NotityUpdateComposition(WidgetGUIEvent* aEvent)
{
  nsEventStatus status;

  // When compositon start, notify the rect of first offset character.
  // When not compositon start, notify the rect of selected composition
  // string if text event.
  if (aEvent->message == NS_COMPOSITION_START) {
    nsCOMPtr<nsIWidget> widget = mPresContext->GetRootWidget();
    // Update composition start offset
    WidgetQueryContentEvent selectedTextEvent(true,
                                              NS_QUERY_SELECTED_TEXT,
                                              widget);
    widget->DispatchEvent(&selectedTextEvent, status);
    if (selectedTextEvent.mSucceeded) {
      mCompositionStartOffset = selectedTextEvent.mReply.mOffset;
    } else {
      // Unknown offset
      NS_WARNING("Cannot get start offset of IME composition");
      mCompositionStartOffset = 0;
    }
    mCompositionTargetOffset = mCompositionStartOffset;
  } else if (aEvent->eventStructType != NS_TEXT_EVENT) {
    return;
  } else {
    WidgetTextEvent* textEvent = aEvent->AsTextEvent();
    mCompositionTargetOffset = mCompositionStartOffset;

    for (uint32_t i = 0; i < textEvent->rangeCount; i++) {
      TextRange& range = textEvent->rangeArray[i];
      if (range.mRangeType == NS_TEXTRANGE_SELECTEDRAWTEXT ||
          range.mRangeType == NS_TEXTRANGE_SELECTEDCONVERTEDTEXT) {
        mCompositionTargetOffset += range.mStartOffset;
        break;
      }
    }
  }

  NotifyIME(widget::NotificationToIME::NOTIFY_IME_OF_COMPOSITION_UPDATE);
}