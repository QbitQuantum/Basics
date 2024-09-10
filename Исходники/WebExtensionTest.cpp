static void methodCallCallback(GDBusConnection* connection, const char* sender, const char* objectPath, const char* interfaceName, const char* methodName, GVariant* parameters, GDBusMethodInvocation* invocation, gpointer userData)
{
    if (g_strcmp0(interfaceName, "org.webkit.gtk.WebExtensionTest"))
        return;

    if (!g_strcmp0(methodName, "GetTitle")) {
        uint64_t pageID;
        g_variant_get(parameters, "(t)", &pageID);
        WebKitWebPage* page = getWebPage(WEBKIT_WEB_EXTENSION(userData), pageID, invocation);
        if (!page)
            return;

        WebKitDOMDocument* document = webkit_web_page_get_dom_document(page);
        GUniquePtr<char> title(webkit_dom_document_get_title(document));
        g_dbus_method_invocation_return_value(invocation, g_variant_new("(s)", title.get()));
    } else if (!g_strcmp0(methodName, "RunJavaScriptInIsolatedWorld")) {
        uint64_t pageID;
        const char* script;
        g_variant_get(parameters, "(t&s)", &pageID, &script);
        WebKitWebPage* page = getWebPage(WEBKIT_WEB_EXTENSION(userData), pageID, invocation);
        if (!page)
            return;

        GRefPtr<WebKitScriptWorld> world = adoptGRef(webkit_script_world_new());
        g_assert(webkit_script_world_get_default() != world.get());
        WebKitFrame* frame = webkit_web_page_get_main_frame(page);
        JSGlobalContextRef jsContext = webkit_frame_get_javascript_context_for_script_world(frame, world.get());
        JSRetainPtr<JSStringRef> jsScript(Adopt, JSStringCreateWithUTF8CString(script));
        JSEvaluateScript(jsContext, jsScript.get(), 0, 0, 0, 0);
        g_dbus_method_invocation_return_value(invocation, 0);
    } else if (!g_strcmp0(methodName, "AbortProcess")) {
        abort();
    } else if (!g_strcmp0(methodName, "GetInitializationUserData")) {
        g_assert(initializationUserData);
        g_assert(g_variant_is_of_type(initializationUserData.get(), G_VARIANT_TYPE_STRING));
        g_dbus_method_invocation_return_value(invocation, g_variant_new("(s)",
            g_variant_get_string(initializationUserData.get(), nullptr)));
    } else if (!g_strcmp0(methodName, "GetProcessIdentifier")) {
        g_dbus_method_invocation_return_value(invocation,
            g_variant_new("(u)", static_cast<guint32>(getCurrentProcessID())));
    }
}