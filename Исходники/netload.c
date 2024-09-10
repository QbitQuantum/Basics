static void monitor_read_config(Control *ctrl, xmlNodePtr node)
{
    xmlChar *value;
    t_global_monitor *global;

    global = (t_global_monitor *)ctrl->data;
    
    if (node == NULL || node->children == NULL)
    {
        return;
    }
    
    for (node = node->children; node; node = node->next)
    {
        if (xmlStrEqual(node->name, (const xmlChar *)MONITOR_ROOT))
        {
            if ((value = xmlGetProp(node, (const xmlChar *)"Use_Label")))
            {
                global->monitor->options.use_label = atoi(value);
                g_free(value);
            }
            if ((value = xmlGetProp(node, (const xmlChar *)"Color_In")))
            {
                gdk_color_parse(value,
                                &global->monitor->options.color[IN]);
                g_free(value);
            }
            if ((value = xmlGetProp(node, (const xmlChar *)"Color_Out")))
            {
                gdk_color_parse(value,
                                &global->monitor->options.color[OUT]);
                g_free(value);
            }
            if ((value = xmlGetProp(node, (const xmlChar *) "Text")))
            {
                if (global->monitor->options.label_text)
                    g_free(global->monitor->options.label_text);
                global->monitor->options.label_text =
                    g_strdup((gchar *)value);
                g_free(value);
            }
            if ((value = xmlGetProp(node, (const xmlChar *) "Network_Device")))
            {
                if (global->monitor->options.network_device)
                    g_free(global->monitor->options.network_device);
                global->monitor->options.network_device =
                    g_strdup((gchar *)value);
                g_free(value);
            }
            if ((value = xmlGetProp(node, (const xmlChar *) "Max_In")))
            {
                global->monitor->options.max[IN] = atoi( value );
                g_free(value);
            }
            if ((value = xmlGetProp(node, (const xmlChar *) "Max_Out")))
            {
                global->monitor->options.max[OUT] = atol( value );
                g_free(value);
            }
            if ((value = xmlGetProp(node, (const xmlChar *) "Auto_Max")))
            {
                global->monitor->options.auto_max = atol(value);
                g_free(value);
            }
            if ((value = xmlGetProp(node, (const xmlChar *) "Update_Interval")))
            {
                global->monitor->options.update_interval = atoi(value);
                g_free(value);
            }
            break;
        }
    }
    setup_monitor(global);
}