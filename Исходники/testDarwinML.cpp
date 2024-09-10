void testPCA()
{
    VectorXd mu = VectorXd::Zero(5);
    MatrixXd sigma(5, 5);
    sigma << 0.99100, 0.91660, 1.04247, 0.75531, 0.49842,
        0.91660, 2.00318, 1.81101, 0.51745, 1.00774,
        1.04247, 1.81101, 2.09615, 0.55339, 1.36639,
        0.75531, 0.51745, 0.55339, 0.67500, 0.15996,
        0.49842, 1.00774, 1.36639, 0.15996, 1.16316;

    drwnPCA pca(drwnSuffStats(1.0, mu, sigma));

    pca.dump();

    drwnXMLDoc xml;
    drwnXMLNode *node = drwnAddXMLChildNode(xml, "test", NULL, false);
    pca.save(*node);

    drwnXMLNode* child = node->first_node("translation");
    VectorXd translation;
    drwnXMLUtils::deserialize(*child, translation);
    cout << translation.transpose() << endl;

    child = node->first_node("projection");
    MatrixXd projection;
    drwnXMLUtils::deserialize(*child, projection);
    cout << projection << endl;

    sigma = projection * sigma * projection.transpose();
    drwnPCA pca2(drwnSuffStats(1.0, mu, sigma));

    xml.clear();
    node = drwnAddXMLChildNode(xml, "test", NULL, false);
    pca2.save(*node);

    child = node->first_node("translation");
    drwnXMLUtils::deserialize(*child, translation);
    cout << translation.transpose() << endl;

    child = node->first_node("projection");
    drwnXMLUtils::deserialize(*child, projection);
    cout << projection << endl;
}