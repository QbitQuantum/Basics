static void webkit_web_view_container_remove(GtkContainer* container, GtkWidget* widget)
{
    //WebKitWebView* webView = WEBKIT_WEB_VIEW(container);
    ////WebKitWebViewPrivate* priv = webView->priv;

    if (children.contains(widget)) {
        gtk_widget_unparent(widget);
        children.remove(widget);
    }
}