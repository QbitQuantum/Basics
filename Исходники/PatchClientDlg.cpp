bool
CPatchDlg::patchProgress(Ice::Long, Ice::Long, Ice::Long totalProgress, Ice::Long totalSize)
{
    IceUtil::Time elapsed = IceUtil::Time::now(IceUtil::Time::Monotonic) - _startTime;
    if(elapsed.toSeconds() > 0)
    {
        CString speed;
        speed.Format(L" %s/s", convertSize(totalProgress / elapsed.toSeconds()));
        _speed->SetWindowText(speed);
    }

    int pcnt = 100;
    if(totalSize > 0)
    {
        pcnt = static_cast<int>(totalProgress * 100 / totalSize);
    }
    CString percent;
    percent.Format(L"%d%%", pcnt);
    _percent->SetWindowText(percent);

    CString total;
    total.Format(L" %s / %s", convertSize(totalProgress), convertSize(totalSize));
    _total->SetWindowText(total);

    _progress->SetPos(pcnt);

    processMessages();
    return !_isCancel;
}