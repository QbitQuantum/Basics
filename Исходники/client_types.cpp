int APP::write(MIOFILE& out) {
    out.printf(
        "<app>\n"
        "    <name>%s</name>\n"
        "    <user_friendly_name>%s</user_friendly_name>\n"
        "    <non_cpu_intensive>%d</non_cpu_intensive>\n"
        "</app>\n",
        name, user_friendly_name,
        non_cpu_intensive?1:0
    );
    return 0;
}