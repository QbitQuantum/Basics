EllipsoidNode::EllipsoidNode(VRMLParser& parser)
    :radius(6378137.0),
     flatteningFactor(1.0/298.257223563),
     scaleFactor(1.0e-3)
{
    /* Check for the opening brace: */
    if(!parser.isToken("{"))
        Misc::throwStdErr("EllipsoidNode::EllipsoidNode: Missing opening brace in node definition");
    parser.getNextToken();

    /* Process attributes until closing brace: */
    while(!parser.isToken("}"))
    {
        if(parser.isToken("radius"))
        {
            /* Parse the ellipsoid radius: */
            parser.getNextToken();
            radius=atof(parser.getToken());
            parser.getNextToken();
        }
        else if(parser.isToken("flatteningFactor"))
        {
            /* Parse the flattening factor: */
            parser.getNextToken();
            flatteningFactor=atof(parser.getToken());
            parser.getNextToken();
        }
        else if(parser.isToken("inverseFlatteningFactor"))
        {
            /* Parse the inverse flattening factor: */
            parser.getNextToken();
            flatteningFactor=1.0/atof(parser.getToken());
            parser.getNextToken();
        }
        else if(parser.isToken("scaleFactor"))
        {
            /* Parse the scale factor: */
            parser.getNextToken();
            scaleFactor=atof(parser.getToken());
            parser.getNextToken();
        }
        else
            Misc::throwStdErr("EllipsoidNode::EllipsoidNode: unknown attribute \"%s\" in node definition",parser.getToken());
    }

    /* Skip the closing brace: */
    parser.getNextToken();

    /* Calculate derived values: */
    modelRadius=radius*scaleFactor;
    e2=(2.0-flatteningFactor)*flatteningFactor;
}