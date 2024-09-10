//==============================================================================
// Called from the event loop in juce_linux_Messaging in response to SelectionRequest events
void juce_handleSelectionRequest (XSelectionRequestEvent &evt)
{
    ClipboardHelpers::initSelectionAtoms();

    // the selection content is sent to the target window as a window property
    XSelectionEvent reply;
    reply.type = SelectionNotify;
    reply.display = evt.display;
    reply.requestor = evt.requestor;
    reply.selection = evt.selection;
    reply.target = evt.target;
    reply.property = None; // == "fail"
    reply.time = evt.time;

    HeapBlock <char> data;
    int propertyFormat = 0, numDataItems = 0;

    if (evt.selection == XA_PRIMARY || evt.selection == ClipboardHelpers::atom_CLIPBOARD)
    {
        if (evt.target == XA_STRING || evt.target == ClipboardHelpers::atom_UTF8_STRING)
        {
            // translate to utf8
            numDataItems = ClipboardHelpers::localClipboardContent.getNumBytesAsUTF8() + 1;
            data.calloc (numDataItems + 1);
            ClipboardHelpers::localClipboardContent.copyToUTF8 (data, numDataItems);
            propertyFormat = 8; // bits/item
        }
        else if (evt.target == ClipboardHelpers::atom_TARGETS)
        {
            // another application wants to know what we are able to send
            numDataItems = 2;
            propertyFormat = 32; // atoms are 32-bit
            data.calloc (numDataItems * 4);
            Atom* atoms = reinterpret_cast<Atom*> (data.getData());
            atoms[0] = ClipboardHelpers::atom_UTF8_STRING;
            atoms[1] = XA_STRING;
        }
    }
    else
    {
        DBG ("requested unsupported clipboard");
    }

    if (data != nullptr)
    {
        const int maxReasonableSelectionSize = 1000000;

        // for very big chunks of data, we should use the "INCR" protocol , which is a pain in the *ss
        if (evt.property != None && numDataItems < maxReasonableSelectionSize)
        {
            XChangeProperty (evt.display, evt.requestor,
                             evt.property, evt.target,
                             propertyFormat /* 8 or 32 */, PropModeReplace,
                             reinterpret_cast<const unsigned char*> (data.getData()), numDataItems);
            reply.property = evt.property; // " == success"
        }
    }

    XSendEvent (evt.display, evt.requestor, 0, NoEventMask, (XEvent*) &reply);
}