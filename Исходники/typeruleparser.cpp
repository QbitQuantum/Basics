bool TypeRuleParser::endElement(const QString &namespaceURI,
                                const QString &localName, const QString &qName)
{
    Q_UNUSED(namespaceURI);
    Q_UNUSED(qName);

    // Handle all elements in lower case
    QString name(localName.toLower());

    // <rule>
    if (name == xml::rule) {
        errorIfNull(_rule);
        // We require a filter and an action
        if (!_children.top().contains(xml::filter))
            typeRuleErrorLoc(QString("No filter specified for rule in line %1.")
                             .arg(_rule->srcLine()));
        if (!_children.top().contains(xml::action))
            typeRuleErrorLoc(QString("No action specified for rule in line %1.")
                             .arg(_rule->srcLine()));
        // Set the priority
        _rule->setPriority(_priorities.isEmpty() ? 0 : _priorities.top().prio);
        // Pass the rule on to the reader
        _reader->appendRule(_rule, _osfStack.isEmpty() ? 0 : _osfStack.top().osf);
        _rule = 0;
    }
    // <ruleinclude>
    else if (name == xml::ruleinclude)
        _reader->appendRulesInclude(_cdata.trimmed());
    // <scriptinclude>
    else if (name == xml::scriptinclude)
        _reader->appendScriptInclude(_cdata.trimmed());
    // <include>
    else if (name == xml::include) {
        bool ret = _reader->includeRulesFile(_cdata.trimmed());
        if (!ret)
            typeRuleErrorLoc(QString("Unable to resolve included file \"%1\".")
                     .arg(_cdata.trimmed()));
    }
    // <name>
    if (name == xml::name) {
        errorIfNull(_rule);
        _rule->setName(_cdata.trimmed());
    }
    // <description>
    if (name == xml::description) {
        errorIfNull(_rule);
        _rule->setDescription(_cdata.trimmed());
    }
    // <action>
    else if (name == xml::action) {
        errorIfNull(_rule);
        errorIfNull(_rule->action());

        switch (_rule->action()->actionType()) {
        case TypeRuleAction::atInlineCode: {
            ProgramScriptAction* action =
                    dynamic_cast<ProgramScriptAction*>(_rule->action());
            action->setSourceCode(_cdata);
            break;
        }
        case TypeRuleAction::atFunction: {
            QString value = _attributes.top().value(xml::file);
            QString file = _reader->absoluteScriptFilePath(value);
            if (file.isEmpty())
                typeRuleErrorLoc(QString("Unable to locate script file \"%1\".")
                         .arg(value));

            FuncCallScriptAction* action =
                    dynamic_cast<FuncCallScriptAction*>(_rule->action());
            action->setFunction(_cdata.trimmed());
            action->setScriptFile(file);
            break;
        }
        case TypeRuleAction::atExpression: {
            if (_children.isEmpty() ||
                !_children.top().contains(xml::srcType) ||
                !_children.top().contains(xml::targetType) ||
                !_children.top().contains(xml::expression))
            {
                typeRuleErrorLoc(QString("Action type \"%1\" in element \"%2\" "
                                         "requires the following child "
                                         "elements: %3, %4, %5")
                                 .arg(xml::expression)
                                 .arg(name)
                                 .arg(xml::srcType)
                                 .arg(xml::targetType)
                                 .arg(xml::expression));
            }
            break;
        }
        default:
            typeRuleErrorLoc(QString("Action type \"%1\" unknown for attribute "
                                  "\"%2\" in element \"%3\".")
                             .arg(_attributes.top().value(xml::type))
                             .arg(xml::type)
                             .arg(name));
        }
    }
    // <sourcetype>
    // <targettype>
    // <expression>
    else if (name == xml::srcType || name == xml::targetType ||
             name == xml::expression)
    {
        errorIfNull(_rule);

        ExpressionAction* action = dynamic_cast<ExpressionAction*>(_rule->action());
        if (!action)
            typeRuleErrorLoc(QString("Element \"%1\" only valid for action "
                                     "type \"%2\".")
                             .arg(name)
                             .arg(xml::expression));

        if (name == xml::srcType)
            action->setSourceTypeStr(_cdata.trimmed());
        else if (name == xml::targetType)
            action->setTargetTypeStr(_cdata.trimmed());
        else
            action->setExpressionStr(_cdata.trimmed());
    }
    // <filter>
    else if (name == xml::filter) {
        errorIfNull(_rule);
        // We require a non-empty filter
        if (_children.top().isEmpty())
            typeRuleErrorLoc(QString("Empty filter specified."));

        _rule->setFilter(_filter);
        _filter = 0;
    }
    // All children of <filter>
    else if (InstanceFilter::supportedFilters().contains(name)) {
        errorIfNull(_filter);
        _filter->parseOption(name, _cdata.trimmed(), &_attributes.top());
    }

    // See if the scope of the OS filter is at its end
    if (!_osfStack.isEmpty() && _osfStack.top().elem == name) {
        // Delete filter and remove it from stack
        delete _osfStack.top().osf;
        _osfStack.pop();
    }

    // See if the scope of the priority is at its end
    if (!_priorities.isEmpty() && _priorities.top().elem == name)
        _priorities.pop();

    // Pop element from stack
    _elems.pop();
    _children.pop();
    _attributes.pop();

    return true;
}