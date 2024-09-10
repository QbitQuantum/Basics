bool
nsXBLWindowKeyHandler::WalkHandlersAndExecute(
                         nsIDOMKeyEvent* aKeyEvent,
                         nsIAtom* aEventType,
                         nsXBLPrototypeHandler* aFirstHandler,
                         uint32_t aCharCode,
                         const IgnoreModifierState& aIgnoreModifierState,
                         bool aExecute,
                         bool* aOutReservedForChrome)
{
  // Try all of the handlers until we find one that matches the event.
  for (nsXBLPrototypeHandler* handler = aFirstHandler;
       handler;
       handler = handler->GetNextHandler()) {
    bool stopped = aKeyEvent->AsEvent()->IsDispatchStopped();
    if (stopped) {
      // The event is finished, don't execute any more handlers
      return false;
    }

    if (aExecute) {
      // If it's executing matched handlers, the event type should exactly be
      // matched.
      if (!handler->EventTypeEquals(aEventType)) {
        continue;
      }
    } else {
      if (handler->EventTypeEquals(nsGkAtoms::keypress)) {
        // If the handler is a keypress event handler, we also need to check
        // if coming keydown event is a preceding event of reserved key
        // combination because if default action of a keydown event is
        // prevented, following keypress event won't be fired.  However, if
        // following keypress event is reserved, we shouldn't allow web
        // contents to prevent the default of the preceding keydown event.
        if (aEventType != nsGkAtoms::keydown &&
            aEventType != nsGkAtoms::keypress) {
          continue;
        }
      } else if (!handler->EventTypeEquals(aEventType)) {
        // Otherwise, aEventType should exactly be matched.
        continue;
      }
    }

    // Check if the keyboard event *may* execute the handler.
    if (!handler->KeyEventMatched(aKeyEvent, aCharCode, aIgnoreModifierState)) {
      continue;  // try the next one
    }

    // Before executing this handler, check that it's not disabled,
    // and that it has something to do (oncommand of the <key> or its
    // <command> is non-empty).
    nsCOMPtr<Element> commandElement;
    if (!GetElementForHandler(handler, getter_AddRefs(commandElement))) {
      continue;
    }

    bool isReserved = false;
    if (commandElement) {
      if (!IsExecutableElement(commandElement)) {
        continue;
      }

      isReserved =
        commandElement->AttrValueIs(kNameSpaceID_None, nsGkAtoms::reserved,
                                    nsGkAtoms::_true, eCaseMatters);
      if (aOutReservedForChrome) {
        *aOutReservedForChrome = isReserved;
      }
    }

    if (!aExecute) {
      if (handler->EventTypeEquals(aEventType)) {
        return true;
      }
      // If the command is reserved and the event is keydown, check also if
      // the handler is for keypress because if following keypress event is
      // reserved, we shouldn't dispatch the event into web contents.
      if (isReserved &&
          aEventType == nsGkAtoms::keydown &&
          handler->EventTypeEquals(nsGkAtoms::keypress)) {
        return true;
      }
      // Otherwise, we've not found a handler for the event yet.
      continue;
    }

    nsCOMPtr<EventTarget> target;
    nsCOMPtr<Element> chromeHandlerElement = GetElement();
    if (chromeHandlerElement) {
      // XXX commandElement may be nullptr...
      target = commandElement;
    } else {
      target = mTarget;
    }

    // XXX Do we execute only one handler even if the handler neither stops
    //     propagation nor prevents default of the event?
    nsresult rv = handler->ExecuteHandler(target, aKeyEvent->AsEvent());
    if (NS_SUCCEEDED(rv)) {
      return true;
    }
  }

#ifdef XP_WIN
  // Windows native applications ignore Windows-Logo key state when checking
  // shortcut keys even if the key is pressed.  Therefore, if there is no
  // shortcut key which exactly matches current modifier state, we should
  // retry to look for a shortcut key without the Windows-Logo key press.
  if (!aIgnoreModifierState.mOS) {
    WidgetKeyboardEvent* keyEvent =
      aKeyEvent->AsEvent()->WidgetEventPtr()->AsKeyboardEvent();
    if (keyEvent && keyEvent->IsOS()) {
      IgnoreModifierState ignoreModifierState(aIgnoreModifierState);
      ignoreModifierState.mOS = true;
      return WalkHandlersAndExecute(aKeyEvent, aEventType, aFirstHandler,
                                    aCharCode, ignoreModifierState, aExecute);
    }
  }
#endif

  return false;
}