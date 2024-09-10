/// @brief Replaces any IDoc parameters with a the specified value from the input IDoc. IDoc
///     parameters should be in the format {IDoc:SegmentName:FieldName}
///     Note you must specify the input IDoc to use by first calling idoc_select_input_file
/// @param a new string with the IDoc parameters replaced with their values
/// @return a new string with the IDoc parameters replaced
IDOCREPLAYDLL_API LPCSTR idoc_eval_string(const LPCSTR parameterizedString)
{
    if (!ensure_valid_license())
    {
        return parameterizedString;
    }

    if (parameterizedString == NULL)
    {
        lr_error_message("Parameterized string cannot be empty.");
        return parameterizedString;
    }

    // TODO: move this check so that it only throws an error when parameterizedString contains something that looks like an IDoc parameter (i.e. {IDoc:xxx:yyy}
    // We don't want an error to be raised when idoc_create() is called with standard LoadRunner parameters.
    if (g_idocParamInputFilePath.empty())
    {
    //    lr_error_message("Input file is not selected. (Call idoc_select_input_file first.)");
        return parameterizedString;
    }

    g_allocatedStrings.push_back(std::string());

    string& result = g_allocatedStrings.back();

    const char* currentString = parameterizedString;

    cmatch matchResults;
    while (regex_search(currentString, matchResults, g_parameterRegex) && matchResults.size() == 3)
    {
        const cmatch::difference_type offset = matchResults.position();
        if (offset > 0)
        {
            result.append(currentString, offset);
            currentString += offset;
        }

        const sub_match<const char*> entireMatch = matchResults[0];
        const sub_match<const char*> segmentMatch = matchResults[1];
        const sub_match<const char*> fieldMatch = matchResults[2];

        const string segment(segmentMatch.first, segmentMatch.length());
        const string field(fieldMatch.first, fieldMatch.length());

        const xml_node segmentNode = get_node_value(g_idocParamInputFile.root(), segment);
        const xml_node fieldNode = get_node_value(segmentNode, field);

        if (segmentNode.empty() || fieldNode.empty())
        {
            result.append(currentString, entireMatch.length());
            currentString += entireMatch.length();

            if (is_param_log_enabled())
            {
                lr_output_message(
                    "Warning: [IDoc] Unable to find IDoc parameter '%s:%s'.",
                    segment.c_str(),
                    field.c_str());
            }

            continue;
        }

        const char_t* value = fieldNode.text().as_string();
        result.append(value);

        if (is_param_log_enabled())
        {
            lr_output_message(
                "[IDoc] Parameter substitution: '%s:%s' => '%s'.",
                segment.c_str(),
                field.c_str(),
                value);
        }

        currentString += entireMatch.length();
    }

    result.append(currentString);

    return result.c_str();
}