void UiWindow::ShowProgressDlg(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);
    if (args.Length() == 0) {
        return;
    }
    auto dlg = ProgressDialog::CreateNew(args);
    ShowProgressDlg(dlg);
}