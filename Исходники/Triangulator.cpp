void  Triangulator::CreateChibiLoopTree(List<ChibiLoopNode> &LoopNodeList, List<DWORD> &LoopRefs, List<LoopVerts> &LoopList)
{
    int i, j;

    // find top loops

    /*for(i=0; i<LoopRefs.Num(); i++)
    {
        LoopVerts &loop1 = LoopList[LoopRefs[i]];
        BOOL bTopLoop = TRUE;
        //Vect2 &testVert = Verts[LoopList[LoopRefs[i]][0].v1];

        List<DWORD> ChildRefs;

        for(j=0; j<LoopRefs.Num(); j++)
        {
            if(j == i)
                continue;

            LoopVerts &loop2 = LoopList[LoopRefs[j]];

            DWORD val = LoopInsideLoop(loop2, loop1);

            if(val == 2)
            {
                if(!ChibiLoopFacingUp(loop2))
                    val = 1;
            }

            if(val == 1)
            {
                bTopLoop = FALSE;
                break;
            }
            else if(LoopInsideLoop(loop1, loop2))
                ChildRefs << LoopRefs[j];
        }

        if(bTopLoop)
        {
            ChibiLoopNode &chibiLoopNode = *LoopNodeList.CreateNew();
            chibiLoopNode.loop = LoopRefs[i];

            CreateChibiLoopTree(chibiLoopNode.Children, ChildRefs, LoopList);
        }
    }*/

    for(i=0; LoopRefs.Num(); i++)  //works like a while(LoopRefs.Num())
    {
        LoopVerts &loop1 = LoopList[LoopRefs[i]];
        BOOL bTopLoop = TRUE;

        List<DWORD> ChildRefs;

        ChildRefs.Clear();

        for(j=0; j<LoopRefs.Num(); j++)
        {
            if(j == i)
                continue;

            LoopVerts &loop2 = LoopList[LoopRefs[j]];

            DWORD val = LoopInsideLoop(loop2, loop1);

            if(val == 2)
            {
                if(!ChibiLoopFacingUp(loop2))
                    val = 1;
            }

            if(val == 1)
            {
                bTopLoop = FALSE;
                break;
            }
            else
            {
                DWORD val2 = LoopInsideLoop(loop1, loop2);
                if((val2 == 1) || ((val2 & val) == 2))
                    ChildRefs << LoopRefs[j];
            }
        }

        if(bTopLoop)
        {
            ChibiLoopNode &chibiLoopNode = *LoopNodeList.CreateNew();
            chibiLoopNode.loop = LoopRefs[i];

            LoopRefs.Remove(i);

            if(ChildRefs.Num())
            {
                for(j=0; j<ChildRefs.Num(); j++)
                    LoopRefs.RemoveItem(ChildRefs[j]);

                CreateChibiLoopTree(chibiLoopNode.Children, ChildRefs, LoopList);
            }

            i=-1; //because it'll do the i++
        }
    }
}