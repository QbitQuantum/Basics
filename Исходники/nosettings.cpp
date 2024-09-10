bool NoSettings::Parse(NoFile& file, NoString& error)
{
    NoString line;
    uint lineNum = 0;
    NoSettings* activeConfig = this;
    std::stack<ConfigStackEntry> configStack;
    bool commented = false; // support for /**/ style comments

    if (!file.Seek(0)) {
        error = "Could not seek to the beginning of the config.";
        return false;
    }

    while (file.ReadLine(line)) {
        lineNum++;

#define ERROR(arg)                                             \
    do {                                                       \
        std::stringstream stream;                              \
        stream << "Error on line " << lineNum << ": " << arg; \
        error = stream.str();                              \
        m_subConfigs.clear();                                  \
        m_entries.clear();                                     \
        return false;                                          \
    } while (0)

        // Remove all leading spaces and trailing line endings
        line.trimLeft();
        line.trimRight("\r\n");

        if (commented || line.startsWith("/*")) {
            /* Does this comment end on the same line again? */
            commented = !line.endsWith("*/");

            continue;
        }

        if (line.empty() || line.startsWith("#") || line.startsWith("//")) {
            continue;
        }

        if (line.startsWith("<") && line.endsWith(">")) {
            line.leftChomp(1);
            line.rightChomp(1);
            line.trim();

            NoString tag = No::token(line, 0);
            NoString value = No::tokens(line, 1);

            tag.trim();
            value.trim();

            if (tag.startsWith("/")) {
                tag = tag.substr(1);

                if (!value.empty())
                    ERROR("Malformated closing tag. Expected \"</" << tag << ">\".");
                if (configStack.empty())
                    ERROR("Closing tag \"" << tag << "\" which is not open.");

                const struct ConfigStackEntry& entry = configStack.top();
                NoSettings myConfig(entry.config);
                NoString name(entry.name);

                if (!tag.equals(entry.tag))
                    ERROR("Closing tag \"" << tag << "\" which is not open.");

                // This breaks entry
                configStack.pop();

                if (configStack.empty())
                    activeConfig = this;
                else
                    activeConfig = &configStack.top().config;

                SubConfig& conf = activeConfig->m_subConfigs[tag.toLower()];
                SubConfig::const_iterator it = conf.find(name);

                if (it != conf.end())
                    ERROR("Duplicate entry for tag \"" << tag << "\" name \"" << name << "\".");

                conf[name] = NoSettingsEntry(myConfig);
            } else {
                if (value.empty())
                    ERROR("Empty block name at begin of block.");
                configStack.push(ConfigStackEntry(tag.toLower(), value));
                activeConfig = &configStack.top().config;
            }

            continue;
        }

        // If we have a regular line, figure out where it goes
        NoString name = No::token(line, 0, "=");
        NoString value = No::tokens(line, 1, "=");

        // Only remove the first space, people might want
        // leading spaces (e.g. in the MOTD).
        if (value.startsWith(" "))
            value.leftChomp(1);

        // We don't have any names with spaces, trim all
        // leading/trailing spaces.
        name.trim();

        if (name.empty() || value.empty())
            ERROR("Malformed line");

        NoString sNameLower = name.toLower();
        activeConfig->m_entries[sNameLower].push_back(value);
    }

    if (commented)
        ERROR("Comment not closed at end of file.");

    if (!configStack.empty()) {
        const NoString& tag = configStack.top().tag;
        ERROR("Not all tags are closed at the end of the file. Inner-most open tag is \"" << tag << "\".");
    }

    return true;
}