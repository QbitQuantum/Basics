void TestDeformer::_deform_on_one_mesh(MDataBlock& data,
                                      MItGeometry& iter,
                                      const MMatrix& localToWorldMatrix,
                                      unsigned int mIndex,
                                      MObject &driver_mesh,
                                      const MDataHandle &envelopeHandle, MArrayDataHandle &vertMapArrayData, MPointArray &tempOutputPts)
{
    MStatus status;

    float env = envelopeHandle.asFloat();

    // use driver_meshVertIter to walk through the vertex of the current driver mesh
    MItMeshVertex driver_meshVertIter( driver_mesh, &status );
    CHECK_MSTATUS( status );

    int i = 0;
    iter.reset();
    while( !iter.isDone(&status) )
    {
        CHECK_MSTATUS( status );

        // get the weight
        float weight = weightValue( data, mIndex, iter.index() ); //painted weight
        float ww = weight * env;

        if ( fabs(ww) > FLT_EPSILON )//if ( ww != 0 )
        {
            __debug("%s(), vertMapArrayData.elementCount()=%d, iter.index()=%d",
                    __FUNCTION__, vertMapArrayData.elementCount(), iter.index());

            // get index_mapped to which the currrent vertex vI is mapped
            CHECK_MSTATUS(vertMapArrayData.jumpToElement(iter.index()));
            int index_mapped = vertMapArrayData.inputValue(&status).asInt();
            CHECK_MSTATUS( status );

            if( index_mapped >= 0 )
            {
                __debug("index_mapped=%d", index_mapped);

                int prevInt;
                CHECK_MSTATUS( driver_meshVertIter.setIndex(index_mapped, prevInt) );

                // vertex wrold position on driver mesh
                MPoint mappedPt = driver_meshVertIter.position( MSpace::kWorld, &status );
                CHECK_MSTATUS( status );
                // vertex wrold position on driven mesh
                MPoint iterPt = iter.position(MSpace::kObject, &status) * localToWorldMatrix;
                CHECK_MSTATUS( status );

                // use ww to interpolate between mappedPt and iterPt
                MPoint pt = iterPt + ((mappedPt - iterPt) * ww );
                pt = pt * localToWorldMatrix.inverse();

                /// put the deform points to tempOutputPts
                tempOutputPts[i] += pt;
            }
        }//if
        CHECK_MSTATUS(iter.next());
        ++i;
    }//while
}