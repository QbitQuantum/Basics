static void ShowProperties(HWND parent, Controller *ctrl, bool extended=false)
{
    PropertiesLayout *layoutData = FindPropertyWindowByParent(parent);
    if (layoutData) {
        SetActiveWindow(layoutData->hwnd);
        return;
    }

    if (!ctrl)
        return;
    layoutData = new PropertiesLayout();
    gPropertiesWindows.Append(layoutData);
    GetProps(ctrl, layoutData, extended);

    if (!CreatePropertiesWindow(parent, layoutData))
        delete layoutData;
}