static void test2() 
{
    const size32_t recsize = 17;
    printf("Test DFS\n");
    StringBuffer s;
    unsigned i;
    unsigned n;
    unsigned t;
    queryNamedGroupStore().remove("daregress_group");
    queryDistributedFileDirectory().removeEntry("daregress::superfile1");
    SocketEndpointArray epa;
    for (n=0;n<400;n++) {
        s.clear().append("192.168.").append(n/256).append('.').append(n%256);
        SocketEndpoint ep(s.str());
        epa.append(ep);
    }
    Owned<IGroup> group = createIGroup(epa); 
    queryNamedGroupStore().add("daregress_group",group,true);
    if (!queryNamedGroupStore().find(group,s.clear()))
        ERROR("Created logical group not found");
    if (stricmp(s.str(),"daregress_group")!=0)
        ERROR("Created logical group found with wrong name");
    group.setown(queryNamedGroupStore().lookup("daregress_group"));
    if (!group)
        ERROR("named group lookup failed");
    printf("Named group created    - 400 nodes\n");
    for (i=0;i<100;i++) {
        Owned<IPropertyTree> pp = createPTree("Part");
        Owned<IFileDescriptor>fdesc = createFileDescriptor();
        fdesc->setDefaultDir("c:\\thordata\\regress");
        n = 9;
        for (unsigned k=0;k<400;k++) {
            s.clear().append("192.168.").append(n/256).append('.').append(n%256);
            Owned<INode> node = createINode(s.str());
            pp->setPropInt64("@size",(n*777+i)*recsize);
            s.clear().append("daregress_test").append(i).append("._").append(n+1).append("_of_400");
            fdesc->setPart(n,node,s.str(),pp);
            n = (n+9)%400;
        }
        fdesc->queryProperties().setPropInt("@recordSize",17);
        s.clear().append("daregress::test").append(i);
        queryDistributedFileDirectory().removeEntry(s.str());
        StringBuffer cname;
        Owned<IDistributedFile> dfile = queryDistributedFileDirectory().createNew(fdesc);
        if (stricmp(dfile->getClusterName(0,cname),"daregress_group")!=0)
            ERROR1("Cluster name wrong %d",i);
        s.clear().append("daregress::test").append(i);
        dfile->attach(s.str());
    }
    printf("DFile create done      - 100 files\n");
    unsigned samples = 5;
    t = 33;
    for (i=0;i<100;i++) {
        s.clear().append("daregress::test").append(t);
        if (!queryDistributedFileDirectory().exists(s.str())) 
            ERROR1("Could not find %s",s.str());
        Owned<IDistributedFile> dfile = queryDistributedFileDirectory().lookup(s.str());
        if (!dfile) {
            ERROR1("Could not find %s",s.str());
            continue;
        }
        offset_t totsz = 0;
        n = 11;
        for (unsigned k=0;k<400;k++) {
            Owned<IDistributedFilePart> part = dfile->getPart(n);
            if (!part) {
                ERROR2("part not found %d %d",t,n);
                continue;
            }
            s.clear().append("192.168.").append(n/256).append('.').append(n%256);
            Owned<INode> node = createINode(s.str());
            if (!node->equals(part->queryNode()))
                ERROR2("part node mismatch %d, %d",t,n);
            if (part->getFileSize(false,false)!=(n*777+t)*recsize)
                ERROR4("size node mismatch %d, %d, %d, %d",t,n,(unsigned)part->getFileSize(false,false),(n*777+t)*recsize);
            s.clear().append("daregress_test").append(t).append("._").append(n+1).append("_of_400");
/* ** TBD
            if (stricmp(s.str(),part->queryPartName())!=0)
                ERROR4("part name mismatch %d, %d '%s' '%s'",t,n,s.str(),part->queryPartName());
*/
            totsz += (n*777+t)*recsize;
            if ((samples>0)&&(i+n+t==k)) {
                samples--;
                RemoteFilename rfn;
                part->getFilename(rfn,samples%2);
                StringBuffer fn;
                rfn.getRemotePath(fn);
                printf("SAMPLE: %d,%d %s\n",t,n,fn.str());
            }
            n = (n+11)%400;
        }
        if (totsz!=dfile->getFileSize(false,false))
            ERROR1("total size mismatch %d",t);
        t = (t+33)%100; 
    }
    printf("DFile lookup done      - 100 files\n");

    // check iteration
    __int64 crctot = 0;
    unsigned np = 0;
    unsigned totrows = 0;
    Owned<IDistributedFileIterator> fiter = queryDistributedFileDirectory().getIterator("daregress::*",false); 
    Owned<IDistributedFilePartIterator> piter;
    ForEach(*fiter) {
        piter.setown(fiter->query().getIterator()); 
        ForEach(*piter) {
            RemoteFilename rfn;
            StringBuffer s;
            piter->query().getFilename(rfn,0);
            rfn.getRemotePath(s);
            piter->query().getFilename(rfn,1);
            rfn.getRemotePath(s);
            crctot += crc32(s.str(),s.length(),0);
            np++;
            totrows += (unsigned)(piter->query().getFileSize(false,false)/fiter->query().queryProperties().getPropInt("@recordSize",-1));
        }
    }
    piter.clear();
    fiter.clear();
    printf("DFile iterate done     - %d parts, %d rows, CRC sum %"I64F"d\n",np,totrows,crctot);
    Owned<IDistributedSuperFile> sfile;
    sfile.setown(queryDistributedFileDirectory().createSuperFile("daregress::superfile1",true));
    for (i = 0;i<100;i++) {
        s.clear().append("daregress::test").append(i);
        sfile->addSubFile(s.str());
    }
    sfile.clear();
    sfile.setown(queryDistributedFileDirectory().lookupSuperFile("daregress::superfile1"));
    if (!sfile) {
        ERROR("Could not find added superfile");
        return;
    }
    __int64 savcrc = crctot;
    crctot = 0;
    np = 0;
    totrows = 0;
    size32_t srs = (size32_t)sfile->queryProperties().getPropInt("@recordSize",-1);
    if (srs!=17)
        ERROR1("Superfile does not match subfile row size %d",srs);
    piter.setown(sfile->getIterator()); 
    ForEach(*piter) {
        RemoteFilename rfn;
        StringBuffer s;
        piter->query().getFilename(rfn,0);
        rfn.getRemotePath(s);
        piter->query().getFilename(rfn,1);
        rfn.getRemotePath(s);
        crctot += crc32(s.str(),s.length(),0);
        np++;
        totrows += (unsigned)(piter->query().getFileSize(false,false)/srs);
    }
    piter.clear();
    printf("Superfile iterate done - %d parts, %d rows, CRC sum %"I64F"d\n",np,totrows,crctot);
    if (crctot!=savcrc)
        ERROR("SuperFile does not match sub files");
    unsigned tr = (unsigned)(sfile->getFileSize(false,false)/srs); 
    if (totrows!=tr)
        ERROR1("Superfile size does not match part sum %d",tr);
    sfile->detach();
    sfile.clear();
    sfile.setown(queryDistributedFileDirectory().lookupSuperFile("daregress::superfile1"));
    if (sfile)
        ERROR("Superfile deletion failed");
    t = 37;
    for (i=0;i<100;i++) {
        s.clear().append("daregress::test").append(t);
        if (i%1) {
            Owned<IDistributedFile> dfile = queryDistributedFileDirectory().lookup(s.str());
            if (!dfile)
                ERROR1("Could not find %s",s.str());
            dfile->detach();
        }
        else 
            queryDistributedFileDirectory().removeEntry(s.str());
        t = (t+37)%100; 
    }
    printf("DFile removal complete\n");
    t = 39;
    for (i=0;i<100;i++) {
        if (queryDistributedFileDirectory().exists(s.str()))
            ERROR1("Found %s after deletion",s.str());
        Owned<IDistributedFile> dfile = queryDistributedFileDirectory().lookup(s.str());
        if (dfile)
            ERROR1("Found %s after deletion",s.str());
        t = (t+39)%100; 
    }
    printf("DFile removal check complete\n");
    queryNamedGroupStore().remove("daregress_group");
    if (queryNamedGroupStore().lookup("daregress_group"))
        ERROR("Named group not removed");
}