const treeLeaf<Type>* treeNode<Type>::findLeafLineOctant
(
    const int level,
    const Type& shapes,
    const label octant,
    const vector& direction,
    point& start,
    const point& end
) const
{
    static const char* functionName =
        "treeNode<Type>::findLeafLineOctant"
        "(const int, const Type&, const label, const vector&,"
        " point&, const point&)";

    if (debug & 2)
    {
        space(Pout, 2*level);
        Pout<< "findLeafLineOctant : bb:" << this->bb()
            << "  start:" << start
            << "  end:" << end
            << "  mid:" << mid()
            << " Searching octant:" << octant
            << endl;
    }

    if (subNodes()[octant])
    {
        if (isNode(octant))
        {
            // Node: recurse into subnodes
            const treeNode<Type>* subNodePtr = getNodePtr(octant);

            if (subNodePtr->bb().contains(direction, start))
            {
                // Search on lower level
                const treeLeaf<Type>* subLeafPtr =
                    subNodePtr->findLeafLine
                    (
                        level + 1,
                        shapes,
                        start,
                        end
                    );

                if (debug & 2)
                {
                    space(Pout, 2*level);
                    Pout<< "findLeafLineOctant : bb:" << this->bb()
                        << " returning from sub treeNode"
                        << " with start:" << start << "  subLeaf:"
                        << long(subLeafPtr) << endl;
                }

                return subLeafPtr;
            }
            else
            {
                FatalErrorIn(functionName)
                    << "Sub node " << subNodePtr->bb()
                    << " at octant " << octant
                    << " does not contain start " << start
                    << abort(FatalError);
            }
        }
        else
        {
            // Leaf
            const treeLeaf<Type>* subLeafPtr = getLeafPtr(octant);

            if (subLeafPtr->bb().contains(direction, start))
            {
                // Step to end of subleaf bb
                point tmp;
                if 
                (
                   !subLeafPtr->bb().intersects
                    (
                        end,
                        start,
                        tmp
                    )
                )
                {
                    FatalErrorIn(functionName)
                        << "Sub leaf contains start " << start
                        << " but line does not intersect its bb "
                        << subLeafPtr->bb()
                        << abort(FatalError);
                }
                start = tmp;

                if (debug & 2)
                {
                    space(Pout, 2*level);
                    Pout<< "findLeafLineOctant : returning from intersecting"
                        << " treeLeaf " << subLeafPtr->bb()
                        << " with start:" << start << "  subLeaf:"
                        << long(subLeafPtr) << endl;
                }

                return subLeafPtr;
            }
            else
            {
                FatalErrorIn(functionName)
                    << "Sub leaf " << subLeafPtr->bb()
                    << " at octant " << octant
                    << " does not contain start " << start
                    << abort(FatalError);
            }
        }
    }
    else
    {
        // Empty subNode. Transfer across.
        const treeBoundBox emptyBb = this->bb().subBbox(mid(), octant);

        if (emptyBb.contains(direction, start))
        {
            if (debug & 2)
            {
                space(Pout, 2*level);
                Pout<< "findLeafLineOctant : Empty node. Octant:" << octant
                    << "  start:" << start
                    << "  bb:" << this->bb()
                    << "  emptyBb:" << emptyBb << endl;
            }

            // Update start by clipping to emptyBb
            point tmp;
            if 
            (
               !emptyBb.intersects
                (
                    end,
                    start,
                    tmp
                )
            )
            {
                FatalErrorIn(functionName)
                    << "Empty node contains start " << start
                    << " but line does not intersect its (calculated)"
                    << " bb " << emptyBb
                    << endl << "This might be due to truncation error"
                    << abort(FatalError);
            }
            start = tmp;

            if (debug & 2)
            {
                space(Pout, 2*level);
                Pout<< "findLeafLineOctant : returning from intersecting with"
                    << " empty " << emptyBb
                    << " with start:" << start << "  subLeaf:" << 0 << endl;
            }

            return NULL;
        }
        else
        {
            FatalErrorIn(functionName)
                << "Empty node " << emptyBb
                << " at octant " << octant
                << " does not contain start " << start
                << abort(FatalError);
        }
    }

    FatalErrorIn(functionName)
        << "Octant " << octant << " of cube " << this->bb()
        << " does not contain start " << start
        << abort(FatalError);

    return NULL;
}