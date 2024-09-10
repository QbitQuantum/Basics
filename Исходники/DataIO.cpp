        std::string parseKeyValue(std::stringstream& stream, std::unique_ptr<DataIO::Node>& node, const std::string& key)
        {
            // Read the assignment symbol from the stream and remove the whitespace behind it
            char chr;
            stream.read(&chr, 1);

            REMOVE_WHITESPACE_AND_COMMENTS(true)

            // Check for subsection as value
            if (stream.peek() == '{')
                return parseSection(stream, node, key);

            // Read the value
            std::string line = trim(readLine(stream));
            if (!line.empty())
            {
                // Remove the ';' if it is there
                if (stream.peek() == ';')
                    stream.read(&chr, 1);

                // Create a value node to store the value
                auto valueNode = std::make_unique<DataIO::ValueNode>();
                valueNode->value = line;

                // It might be a list node
                if ((line.size() >= 2) && (line[0] == '[') && (line.back() == ']'))
                {
                    valueNode->listNode = true;
                    if (line.size() >= 3)
                    {
                        valueNode->valueList.push_back("");

                        std::size_t i = 1;
                        while (i < line.size()-1)
                        {
                            if (line[i] == ',')
                            {
                                i++;
                                valueNode->valueList.back() = trim(valueNode->valueList.back());
                                valueNode->valueList.push_back("");
                            }
                            else if (line[i] == '"')
                            {
                                valueNode->valueList.back().insert(valueNode->valueList.back().getSize(), line[i]);
                                i++;

                                bool backslash = false;
                                while (i < line.size()-1)
                                {
                                    valueNode->valueList.back().insert(valueNode->valueList.back().getSize(), line[i]);

                                    if (line[i] == '"' && !backslash)
                                    {
                                        i++;
                                        break;
                                    }

                                    if (line[i] == '\\' && !backslash)
                                        backslash = true;
                                    else
                                        backslash = false;

                                    i++;
                                }
                            }
                            else
                            {
                                valueNode->valueList.back().insert(valueNode->valueList.back().getSize(), line[i]);
                                i++;
                            }
                        }

                        valueNode->valueList.back() = trim(valueNode->valueList.back());
                    }
                }

                node->propertyValuePairs[toLower(key)] = std::move(valueNode);
                return "";
            }
            else
            {
                if (stream.peek() == EOF)
                    return "Found EOF while trying to read a value.";
                else
                {
                    chr = stream.peek();
                    if (chr == '=')
                        return "Found '=' while trying to read a value.";
                    else if (chr == '{')
                        return "Found '{' while trying to read a value.";
                    else
                        return "Found empty value.";
                }
            }
        }