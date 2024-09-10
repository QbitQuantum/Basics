TEST_F(HTMLSelectElementTest, DefaultToolTip)
{
    document().documentElement()->setInnerHTML("<select size=4><option value="">Placeholder</option><optgroup><option>o2</option></optgroup></select>", ASSERT_NO_EXCEPTION);
    document().view()->updateAllLifecyclePhases();
    HTMLSelectElement* select = toHTMLSelectElement(document().body()->firstChild());
    Element* option = toElement(select->firstChild());
    Element* optgroup = toElement(option->nextSibling());

    EXPECT_EQ(String(), select->defaultToolTip()) << "defaultToolTip for SELECT without FORM and without required attribute should return null string.";
    EXPECT_EQ(select->defaultToolTip(), option->defaultToolTip());
    EXPECT_EQ(select->defaultToolTip(), optgroup->defaultToolTip());

    select->setBooleanAttribute(HTMLNames::requiredAttr, true);
    EXPECT_EQ("<<ValidationValueMissingForSelect>>", select->defaultToolTip()) << "defaultToolTip for SELECT without FORM and with required attribute should return a valueMissing message.";
    EXPECT_EQ(select->defaultToolTip(), option->defaultToolTip());
    EXPECT_EQ(select->defaultToolTip(), optgroup->defaultToolTip());

    HTMLFormElement* form = HTMLFormElement::create(document());
    document().body()->appendChild(form);
    form->appendChild(select);
    EXPECT_EQ("<<ValidationValueMissingForSelect>>", select->defaultToolTip()) << "defaultToolTip for SELECT with FORM and required attribute should return a valueMissing message.";
    EXPECT_EQ(select->defaultToolTip(), option->defaultToolTip());
    EXPECT_EQ(select->defaultToolTip(), optgroup->defaultToolTip());

    form->setBooleanAttribute(HTMLNames::novalidateAttr, true);
    EXPECT_EQ(String(), select->defaultToolTip()) << "defaultToolTip for SELECT with FORM[novalidate] and required attribute should return null string.";
    EXPECT_EQ(select->defaultToolTip(), option->defaultToolTip());
    EXPECT_EQ(select->defaultToolTip(), optgroup->defaultToolTip());

    option->remove();
    optgroup->remove();
    EXPECT_EQ(String(), option->defaultToolTip());
    EXPECT_EQ(String(), optgroup->defaultToolTip());
}