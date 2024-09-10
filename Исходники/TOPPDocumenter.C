void convertINI2HTML(const Param & p, ostream & os)
{
  // the .css file is included via the Header.html (see doc/doxygen/common/Header.html)
  os << "<div class=\"ini_global\">\n";
  os << "<div class=\"legend\">\n";
  os << "<b>Legend:</b><br>\n";
  os << " <div class=\"item item_required\">required parameter</div>\n";
  os << " <div class=\"item item_advanced\">advanced parameter</div>\n";
  os << "</div>\n";

  Param::ParamIterator it = p.begin();
  String indentation = "  ";

  while (it != p.end())
  {
    string key = it.getName();

    //write opened/closed nodes
    const std::vector<Param::ParamIterator::TraceInfo> & trace = it.getTrace();
    for (std::vector<Param::ParamIterator::TraceInfo>::const_iterator it2 = trace.begin(); it2 != trace.end(); ++it2)
    {
      if (it2->opened) //opened node
      {
        String d = it2->description;
        d.substitute("\n", "<br>");
        os << indentation  << "<div class=\"node\"><span class=\"node_name\">" << (String().fillLeft('+', (UInt) indentation.size() / 2) + it2->name) << "</span><span class=\"node_description\">" << (d) << "</span></div>" << "\n";
        indentation += "  ";
      }
      else //closed node
      {
        indentation.resize(indentation.size() - 2);
        //os << indentation << "</div>" << "\n";
      }
    }

    //write item
    String s_attr;
    String s_req;
    if (it->tags.find("advanced") != it->tags.end())
      s_attr += " item_advanced";                                                // optionally add advanced class
    if (it->tags.find("required") != it->tags.end())
      s_req += " item_required";                                                // optionally add required class
    DataValue::DataType value_type = it->value.valueType();
    //write opening tag
    os << indentation << "<div class=\"item" + s_attr + "\"><span class=\"item_name" + s_req + "\" style=\"padding-left:" << indentation.size() * 4 << "px;\">" << (it->name) << "</span><span class=\"item_value\">" << it->value.toString() << "</span>" << "\n";

    //replace all critical characters in description
    String d = it->description;
    d.substitute("\n", "<br>");
    os << "<span class=\"item_description\">" << (d) << "</span>";

    //tags
    String list;
    for (set<String>::const_iterator tag_it = it->tags.begin(); tag_it != it->tags.end(); ++tag_it)
    {
      if (*tag_it == "advanced")
        continue;                        // do not list "advanced" or "required" (this is done by color coding)
      if (*tag_it == "required")
        continue;
      if (!list.empty())
        list += ",";
      list += *tag_it;
    }
    os << "<span class=\"item_tags\">" << (list) << "</span>";

    //restrictions
    String restrictions = "";
    bool escape_restrictions(true);
    switch (value_type)
    {
    case DataValue::INT_VALUE:
    case DataValue::INT_LIST:
    {
      bool min_set = (it->min_int != -numeric_limits<Int>::max());
      bool max_set = (it->max_int != numeric_limits<Int>::max());
      if (max_set || min_set)
      {
        if (min_set)
          restrictions += String(it->min_int);
        else
          restrictions += "-&#8734;";        // infinity symbol
        restrictions += ':';
        if (max_set)
          restrictions += String(it->max_int);
        else
          restrictions += "&#8734;";
      }
      escape_restrictions = false;     // prevent html escape of infinity symbol
    }
    break;

    case DataValue::DOUBLE_VALUE:
    case DataValue::DOUBLE_LIST:
    {
      bool min_set = (it->min_float != -numeric_limits<DoubleReal>::max());
      bool max_set = (it->max_float != numeric_limits<DoubleReal>::max());
      if (max_set || min_set)
      {
        if (min_set)
          restrictions += String(it->min_float);
        else
          restrictions += "-&#8734;";        // infinity symbol
        restrictions += ':';
        if (max_set)
          restrictions += String(it->max_float);
        else
          restrictions += "&#8734;";
      }
      escape_restrictions = false;     // prevent html escape of infinity symbol
    }
    break;

    case DataValue::STRING_VALUE:
    case DataValue::STRING_LIST:
      if (it->valid_strings.size() != 0)
      {
        restrictions.concatenate(it->valid_strings.begin(), it->valid_strings.end(), ",");
      }
      break;

    default:
      break;
    }
    if (restrictions.empty())
      restrictions = " ";                       // create content, such that the cell gets an underline

    os << "<span class=\"item_restrictions\">" << restrictions << "</span>";

    os << "</div>"; // end div item

    ++it;
  }

  os << "</div>\n";  // end global div
}