AlarmListViewItem::AlarmListViewItem(AlarmListView *parent, const KAEvent &event, const QDateTime &now)
    : EventListViewItemBase(parent, event),
      mMessageTruncated(false),
      mTimeToAlarmShown(false)
{
    setLastColumnText();     // set the message column text

    DateTime dateTime = event.expired() ? event.startDateTime() : event.displayDateTime();
    if(parent->column(AlarmListView::TIME_COLUMN) >= 0)
        setText(parent->column(AlarmListView::TIME_COLUMN), alarmTimeText(dateTime));
    if(parent->column(AlarmListView::TIME_TO_COLUMN) >= 0)
    {
        QString tta = timeToAlarmText(now);
        setText(parent->column(AlarmListView::TIME_TO_COLUMN), tta);
        mTimeToAlarmShown = !tta.isNull();
    }
    QTime t = dateTime.time();
    mDateTimeOrder.sprintf("%04d%03d%02d%02d", dateTime.date().year(), dateTime.date().dayOfYear(),
                           t.hour(), t.minute());

    int repeatOrder = 0;
    int repeatInterval = 0;
    QString repeatText = event.recurrenceText(true);     // text displayed in Repeat column
    if(repeatText.isEmpty())
        repeatText = event.repetitionText(true);
    if(event.repeatAtLogin())
        repeatOrder = 1;
    else
    {
        repeatInterval = event.recurInterval();
        switch(event.recurType())
        {
            case KARecurrence::MINUTELY:
                repeatOrder = 2;
                break;
            case KARecurrence::DAILY:
                repeatOrder = 3;
                break;
            case KARecurrence::WEEKLY:
                repeatOrder = 4;
                break;
            case KARecurrence::MONTHLY_DAY:
            case KARecurrence::MONTHLY_POS:
                repeatOrder = 5;
                break;
            case KARecurrence::ANNUAL_DATE:
            case KARecurrence::ANNUAL_POS:
                repeatOrder = 6;
                break;
            case KARecurrence::NO_RECUR:
            default:
                break;
        }
    }
    setText(parent->column(AlarmListView::REPEAT_COLUMN), repeatText);
    mRepeatOrder.sprintf("%c%08d", '0' + repeatOrder, repeatInterval);

    bool showColour = (event.action() == KAEvent::MESSAGE || event.action() == KAEvent::FILE);
    mColourOrder.sprintf("%06u", (showColour ? event.bgColour().rgb() : 0));

    mTypeOrder.sprintf("%02d", event.action());
}