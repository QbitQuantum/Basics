//**************************************************************************
//                         1                   2                   3       *
// Col-> 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2   *
// Row                                                                     *
//  1    -----------------   Appointment                                   *
//  2    |               |              ---------------------              *
//  3    |               |   Phone :   |                    |              *
//  4    |               |              ---------------------              *
//  5    |               |              ---------------------              *
//  6    |               |   Location: |                    |              *
//  7    |               |              ---------------------              *
//  8    |               |             ----------------------              *
//  9    |               |   Subject:  |                    |              *
// 10    |               |             |                    |              *
// 11    |               |             |                    |              *
// 12    -----------------             |                    |              *
// 13                                  ----------------------              *
// 14    Users:       ��������������������������������������������Ŀ       *
// 15                 �                                            �       *
// 16                 �                                            �       *
// 17                 �                                            �       *
// 18                 �                                            �       *
// 19                 �                                            �       *
// 20                 ����������������������������������������������       *
// 21   ������������Ŀ  ������������Ŀ  ������������Ŀ                     *
// 22   �            �  �            �  �            �                     *
// 23   ��������������  ��������������  ��������������                     *
//**************************************************************************
// UpdlDialog :: UpdlDialog - Get a book name                              *
//**************************************************************************
UpdlDialog :: UpdlDialog(_IDL_SEQUENCE_Appointment apptList, long *index,
                         unsigned long windowId, IWindow * ownerWnd)
            : IFrameWindow(windowId,
                           desktopWindow(), // parent
                           ownerWnd,        // owner
                           IRectangle(500,  // width
                                      400), // height
                           IWindow::synchPaint
                            |IWindow::clipSiblings
                            |IWindow::saveBits
                            |systemMenu
                            |titleBar
                            |dialogBorder
                            |dialogBackground
                           ),
              clientCanvas(WND_CANVAS_UPDLDIALOG,this,this),
              buttons(WND_CANVAS_UPDLDIALOGBTN,this,this),
              listBox(LB_APPTS,&clientCanvas,&clientCanvas,IRectangle()),
              multicCanvas(WND_CANVAS_UPDLMCDIALOG,
                               &clientCanvas, &clientCanvas, IRectangle()),
              txtAppointment(STR_APPOINTMENT,&multicCanvas,&multicCanvas),
              txtPhone(STR_PHONE,&multicCanvas,&multicCanvas),
              txtLocation(STR_LOCATION,&multicCanvas,&multicCanvas),
              txtSubject(STR_SUBJECT,&multicCanvas,&multicCanvas),
              fldPhone(DDL_PHONE,&multicCanvas,&multicCanvas),
              fldLocation(DDL_LOCATION,&multicCanvas,&multicCanvas),
              fldSubject(DDL_SUBJECT,&multicCanvas,&multicCanvas),
//            UserCanvas(WND_CANVAS_UPDLUSERDIALOG, &clientCanvas, &clientCanvas),
//            lboxUsers(LB_USERS,&UserCanvas,&UserCanvas),
//            txtUsers(TXT_USERS,&UserCanvas,&UserCanvas),
              btnOk(DID_OK,&buttons,&buttons),
              btnCancel(DID_CANCEL,&buttons,&buttons),
              btnSelect(DID_SELECT,&buttons,&buttons),
              apptList(apptList),
              IDValue(index)
{
  string bp;
  strstream ss;
  Appointment *appt;

  Environment *ev = somGetGlobalEnvironment();

  setClient(&clientCanvas);
  clientCanvas.setOrientation(ISplitCanvas::verticalSplit);
  clientCanvas.setSplitWindowPercentage(&multicCanvas, 60);
  clientCanvas.setSplitWindowPercentage(&listBox, 40);

//UserCanvas.setOrientation(ISplitCanvas::horizontalSplit);

  IWindow::enable(1);
  IHandler::enable(1);
  listBox.enable(1);
  ICommandHandler::handleEventsFor(this); // Set self as command event handler

  if (sequenceLength(apptList)>0) {
     for (int i=0; sequenceLength(apptList)>i; i++) {
        appt = sequenceElement(apptList,i);
        ss << ITime(appt->_get_start(ev)) << " to " << ITime(appt->_get_end(ev)) << endl;
        listBox.addAsLast(bp=ss.str());
        ss.rdbuf()->seekoff(0, ios::beg, ios::in|ios::out);
     }
     ss.rdbuf()->freeze(0); // release string buffer
  }

  txtAppointment.setText(STR_APPOINTMENT);
  txtPhone.setText(STR_PHONE);
  txtLocation.setText(STR_LOCATION);
  txtSubject.setText(STR_SUBJECT);

                                  // Disable until the appointment is selected
  fldLocation.disable();
  fldPhone.disable();
  fldSubject.disable();
  *IDValue = -1;  // Initialize the IDValue

//txtUsers.setText(STR_USERS);

  btnOk.setText(STR_OK);
  btnOk.disable();    // disable until a selection is made
  btnCancel.setText(STR_CANCEL);
  btnSelect.setText(STR_SELECT);
  if (windowId == WND_DELAPPTDIALOG) {     // Set everything to read only
    fldPhone.enableDataUpdate(false);
    fldLocation.enableDataUpdate(false);
    fldSubject.enableDataUpdate(false);
  }

  //                      Field              Col  Row  #Col  #Row
  multicCanvas.addToCell(&txtAppointment  ,    2,   2,   12,   1);

  multicCanvas.addToCell(&txtPhone        ,    2,   3,    2,   1);
  multicCanvas.addToCell(&txtLocation     ,    2,   6,    2,   1);
  multicCanvas.addToCell(&txtSubject      ,    2,   9,    2,   1);

  multicCanvas.addToCell(&fldPhone        ,    6,   3,   10,   1);
  multicCanvas.addToCell(&fldLocation     ,    6,   6,   10,   1);
  multicCanvas.addToCell(&fldSubject      ,    6,   9,   10,   1);

  setFocus();
  buttons.setMargin(ISize());            // Set Canvas Margins to zero
  buttons.setPad(ISize());               // Set Button Canvas Pad to zero
  addExtension(&buttons, IFrameWindow::belowClient,
               (unsigned long)buttons.minimumSize().height()+10);
  listBox.setFocus();
}