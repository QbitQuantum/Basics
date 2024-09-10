void QLCCapability_Test::load()
{
    QDomDocument doc;

    QDomElement root = doc.createElement("Capability");
    doc.appendChild(root);

    root.setAttribute("Min", 13);
    root.setAttribute("Max", 19);

    QDomText name = doc.createTextNode("Test1");
    root.appendChild(name);

    QLCCapability cap;
    QVERIFY(cap.loadXML(root) == true);
    QVERIFY(cap.name() == "Test1");
    QVERIFY(cap.min() == 13);
    QVERIFY(cap.max() == 19);
}