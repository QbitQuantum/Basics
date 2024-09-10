void Qtilities::Testing::TestObserver::testTreeAtContainment() {
    // Example tree using tree node classes to simplify test:
    TreeNode* rootNode = new TreeNode("Root");
    TreeNode* parentNode1 = rootNode->addNode("Parent 1");
    TreeNode* parentNode2 = rootNode->addNode("Parent 2");
    parentNode1->addItem("Child 1");
    parentNode1->addItem("Child 2");
    parentNode2->addItem("Child 3");
    parentNode2->addItem("Child 4");
    TreeItem* item = parentNode2->addItem("Child 5");

    // Now create and add a contained observer:
    TreeNode* containedNode = new TreeNode("Contained Node");
    containedNode->addItem("Contained Item 1");
    containedNode->addItem("Contained Item 2");
    TreeItem* test_item = containedNode->addItem("Contained Item 3");
    containedNode->setParent(item);

    LOG_INFO(QString::number(rootNode->treeCount()));
    QVERIFY(rootNode->treeAt(10) == test_item);
}