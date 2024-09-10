int NET_STATS::parse(MIOFILE& in) {
    char buf[256];

    up.clear();
    down.clear();
    while (in.fgets(buf, 256)) {
        if (match_tag(buf, "</net_stats>")) return 0;
        if (parse_double(buf, "<bwup>", up.max_rate)) continue;
        if (parse_double(buf, "<avg_up>", up.avg_rate)) continue;
        if (parse_double(buf, "<avg_time_up>", up.avg_time)) continue;
        if (parse_double(buf, "<bwdown>", down.max_rate)) continue;
        if (parse_double(buf, "<avg_down>", down.avg_rate)) continue;
        if (parse_double(buf, "<avg_time_down>", down.avg_time)) continue;
        handle_unparsed_xml_warning("NET_STATS::parse", buf);
    }
    return ERR_XML_PARSE;
}