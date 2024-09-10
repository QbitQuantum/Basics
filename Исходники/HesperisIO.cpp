void HesperisIO::LsChildren(MObjectArray & dst, 
	            const int & maxCount,
	            const MObject & oparent)
{
    MFnDagNode ppf(oparent);
    for(unsigned i = 0; i <ppf.childCount(); i++) {
        dst.append(ppf.child(i) );
        if(dst.length() >= maxCount)
            return;
    }
}