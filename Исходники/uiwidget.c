struct OzUIWidget *OzUICreateWidget(struct OzUIWindow *window, int type, int flags, struct Rect *rect, struct OzUIWidgetOperation *ops, void *userData)
{
    struct OzUIWidget *widget;
    widget = (struct OzUIWidget*)malloc(sizeof(struct OzUIWidget));
    memset(widget, 0, sizeof(struct OzUIWidget));
    widget->window = window;
    widget->type = type;
    widget->flags = flags;
    copyRect(&widget->rect, rect);
    translateRect(&widget->rect, widget->window->clientRect.x, widget->window->clientRect.y);
    initRect(&widget->dirtyRect, 0, 0, 0, 0);
    widget->ops = ops;
    widget->d = userData;
    listAdd(&widget->link, &window->widgetList);
    if (widget->ops && widget->ops->onCreate)
        widget->ops->onCreate(widget);
    return widget;
}