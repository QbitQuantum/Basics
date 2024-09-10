void setBrigProp(Inst inst, unsigned propId, unsigned val, bool ignoreErrors)
{
    using namespace HSAIL_PROPS;

    switch(inst.kind())
    {
        case BRIG_KIND_INST_ADDR:
        {
            InstAddr it = inst;

            switch(propId)
            {
            case PROP_OPCODE: it.opcode() = val; break;
            case PROP_TYPE: it.type() = val; break;
            case PROP_SEGMENT: it.segment() = val; break;
            default:
                assert(ignoreErrors);
                break;
            }
        }
        break;

        case BRIG_KIND_INST_ATOMIC:
        {
            InstAtomic it = inst;

            switch(propId)
            {
            case PROP_OPCODE: it.opcode() = val; break;
            case PROP_TYPE: it.type() = val; break;
            case PROP_SEGMENT: it.segment() = val; break;
            case PROP_MEMORYORDER: it.memoryOrder() = val; break;
            case PROP_MEMORYSCOPE: it.memoryScope() = val; break;
            case PROP_ATOMICOPERATION: it.atomicOperation() = val; break;
            case PROP_EQUIVCLASS: it.equivClass() = val; break;
            default:
                assert(ignoreErrors);
                break;
            }
        }
        break;

        case BRIG_KIND_INST_BASIC:
        {
            InstBasic it = inst;

            switch(propId)
            {
            case PROP_OPCODE: it.opcode() = val; break;
            case PROP_TYPE: it.type() = val; break;
            default:
                assert(ignoreErrors);
                break;
            }
        }
        break;

        case BRIG_KIND_INST_BR:
        {
            InstBr it = inst;

            switch(propId)
            {
            case PROP_OPCODE: it.opcode() = val; break;
            case PROP_TYPE: it.type() = val; break;
            case PROP_WIDTH: it.width() = val; break;
            default:
                assert(ignoreErrors);
                break;
            }
        }
        break;

        case BRIG_KIND_INST_CMP:
        {
            InstCmp it = inst;

            switch(propId)
            {
            case PROP_OPCODE: it.opcode() = val; break;
            case PROP_TYPE: it.type() = val; break;
            case PROP_SOURCETYPE: it.sourceType() = val; break;
            case PROP_FTZ: it.modifier().ftz() = (val != 0); break;
            case PROP_COMPARE: it.compare() = val; break;
            case PROP_PACK: it.pack() = val; break;
            default:
                assert(ignoreErrors);
                break;
            }
        }
        break;

        case BRIG_KIND_INST_CVT:
        {
            InstCvt it = inst;

            switch(propId)
            {
            case PROP_OPCODE: it.opcode() = val; break;
            case PROP_TYPE: it.type() = val; break;
            case PROP_SOURCETYPE: it.sourceType() = val; break;
            case PROP_FTZ: it.modifier().ftz() = (val != 0); break;
            case PROP_ROUND: it.round() = val; break;
            default:
                assert(ignoreErrors);
                break;
            }
        }
        break;

        case BRIG_KIND_INST_IMAGE:
        {
            InstImage it = inst;

            switch(propId)
            {
            case PROP_OPCODE: it.opcode() = val; break;
            case PROP_TYPE: it.type() = val; break;
            case PROP_IMAGETYPE: it.imageType() = val; break;
            case PROP_COORDTYPE: it.coordType() = val; break;
            case PROP_GEOMETRY: it.geometry() = val; break;
            case PROP_EQUIVCLASS: it.equivClass() = val; break;
            default:
                assert(ignoreErrors);
                break;
            }
        }
        break;

        case BRIG_KIND_INST_LANE:
        {
            InstLane it = inst;

            switch(propId)
            {
            case PROP_OPCODE: it.opcode() = val; break;
            case PROP_TYPE: it.type() = val; break;
            case PROP_SOURCETYPE: it.sourceType() = val; break;
            case PROP_WIDTH: it.width() = val; break;
            default:
                assert(ignoreErrors);
                break;
            }
        }
        break;

        case BRIG_KIND_INST_MEM:
        {
            InstMem it = inst;

            switch(propId)
            {
            case PROP_OPCODE: it.opcode() = val; break;
            case PROP_TYPE: it.type() = val; break;
            case PROP_SEGMENT: it.segment() = val; break;
            case PROP_ALIGN: it.align() = val; break;
            case PROP_EQUIVCLASS: it.equivClass() = val; break;
            case PROP_WIDTH: it.width() = val; break;
            case PROP_ISCONST: it.modifier().isConst() = (val != 0); break;
            default:
                assert(ignoreErrors);
                break;
            }
        }
        break;

        case BRIG_KIND_INST_MEM_FENCE:
        {
            InstMemFence it = inst;

            switch(propId)
            {
            case PROP_OPCODE: it.opcode() = val; break;
            case PROP_TYPE: it.type() = val; break;
            case PROP_MEMORYORDER: it.memoryOrder() = val; break;
            case PROP_GLOBALSEGMENTMEMORYSCOPE: it.globalSegmentMemoryScope() = val; break;
            case PROP_GROUPSEGMENTMEMORYSCOPE: it.groupSegmentMemoryScope() = val; break;
            case PROP_IMAGESEGMENTMEMORYSCOPE: it.imageSegmentMemoryScope() = val; break;
            default:
                assert(ignoreErrors);
                break;
            }
        }
        break;

        case BRIG_KIND_INST_MOD:
        {
            InstMod it = inst;

            switch(propId)
            {
            case PROP_OPCODE: it.opcode() = val; break;
            case PROP_TYPE: it.type() = val; break;
            case PROP_FTZ: it.modifier().ftz() = (val != 0); break;
            case PROP_ROUND: it.round() = val; break;
            case PROP_PACK: it.pack() = val; break;
            default:
                assert(ignoreErrors);
                break;
            }
        }
        break;

        case BRIG_KIND_INST_QUERY_IMAGE:
        {
            InstQueryImage it = inst;

            switch(propId)
            {
            case PROP_OPCODE: it.opcode() = val; break;
            case PROP_TYPE: it.type() = val; break;
            case PROP_IMAGETYPE: it.imageType() = val; break;
            case PROP_GEOMETRY: it.geometry() = val; break;
            case PROP_IMAGEQUERY: it.imageQuery() = val; break;
            default:
                assert(ignoreErrors);
                break;
            }
        }
        break;

        case BRIG_KIND_INST_QUERY_SAMPLER:
        {
            InstQuerySampler it = inst;

            switch(propId)
            {
            case PROP_OPCODE: it.opcode() = val; break;
            case PROP_TYPE: it.type() = val; break;
            case PROP_SAMPLERQUERY: it.samplerQuery() = val; break;
            default:
                assert(ignoreErrors);
                break;
            }
        }
        break;

        case BRIG_KIND_INST_QUEUE:
        {
            InstQueue it = inst;

            switch(propId)
            {
            case PROP_OPCODE: it.opcode() = val; break;
            case PROP_TYPE: it.type() = val; break;
            case PROP_SEGMENT: it.segment() = val; break;
            case PROP_MEMORYORDER: it.memoryOrder() = val; break;
            default:
                assert(ignoreErrors);
                break;
            }
        }
        break;

        case BRIG_KIND_INST_SEG:
        {
            InstSeg it = inst;

            switch(propId)
            {
            case PROP_OPCODE: it.opcode() = val; break;
            case PROP_TYPE: it.type() = val; break;
            case PROP_SEGMENT: it.segment() = val; break;
            default:
                assert(ignoreErrors);
                break;
            }
        }
        break;

        case BRIG_KIND_INST_SEG_CVT:
        {
            InstSegCvt it = inst;

            switch(propId)
            {
            case PROP_OPCODE: it.opcode() = val; break;
            case PROP_TYPE: it.type() = val; break;
            case PROP_SOURCETYPE: it.sourceType() = val; break;
            case PROP_SEGMENT: it.segment() = val; break;
            case PROP_ISNONULL: it.modifier().isNoNull() = (val != 0); break;
            default:
                assert(ignoreErrors);
                break;
            }
        }
        break;

        case BRIG_KIND_INST_SIGNAL:
        {
            InstSignal it = inst;

            switch(propId)
            {
            case PROP_OPCODE: it.opcode() = val; break;
            case PROP_TYPE: it.type() = val; break;
            case PROP_SIGNALTYPE: it.signalType() = val; break;
            case PROP_MEMORYORDER: it.memoryOrder() = val; break;
            case PROP_SIGNALOPERATION: it.signalOperation() = val; break;
            default:
                assert(ignoreErrors);
                break;
            }
        }
        break;

        case BRIG_KIND_INST_SOURCE_TYPE:
        {
            InstSourceType it = inst;

            switch(propId)
            {
            case PROP_OPCODE: it.opcode() = val; break;
            case PROP_TYPE: it.type() = val; break;
            case PROP_SOURCETYPE: it.sourceType() = val; break;
            default:
                assert(ignoreErrors);
                break;
            }
        }
        break;

        default:
            assert(false); // Invalid format
            break;
    }
}