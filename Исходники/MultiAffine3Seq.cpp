static void readAffine3(const Listing& node, Affine3& out_value)
{
    if(node.size() == 6){

        Affine3::TranslationPart t = out_value.translation();
        t[0] = node[0].toDouble();
        t[1] = node[1].toDouble();
        t[2] = node[2].toDouble();

        const double r = node[3].toDouble();
        const double p = node[4].toDouble();
        const double y = node[5].toDouble();
        
        out_value.linear() = rotFromRpy(r, p, y);
    }
}