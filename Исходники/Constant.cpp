//
// Do single unary node folding
//
// Returns a new node representing the result.
//
TIntermTyped* TIntermConstantUnion::fold(TOperator op, const TType& returnType) const
{
    // First, size the result, which is mostly the same as the argument's size,
    // but not always, and classify what is componentwise.
    // Also, eliminate cases that can't be compile-time constant.
    int resultSize;
    bool componentWise = true;

    int objectSize = getType().computeNumComponents();
    switch (op) {
    case EOpDeterminant:
    case EOpAny:
    case EOpAll:
    case EOpLength:
        componentWise = false;
        resultSize = 1;
        break;

    case EOpEmitStreamVertex:
    case EOpEndStreamPrimitive:
        // These don't actually fold
        return 0;

    case EOpPackSnorm2x16:
    case EOpPackUnorm2x16:
    case EOpPackHalf2x16:
        componentWise = false;
        resultSize = 1;
        break;

    case EOpUnpackSnorm2x16:
    case EOpUnpackUnorm2x16:
    case EOpUnpackHalf2x16:
        componentWise = false;
        resultSize = 2;
        break;

    case EOpNormalize:
        componentWise = false;
        resultSize = objectSize;
        break;

    default:
        resultSize = objectSize;
        break;
    }

    // Set up for processing
    TConstUnionArray newConstArray(resultSize);
    const TConstUnionArray& unionArray = getConstArray();

    // Process non-component-wise operations
    switch (op) {
    case EOpLength:
    case EOpNormalize:
    {
        double sum = 0;
        for (int i = 0; i < objectSize; i++)
            sum += unionArray[i].getDConst() * unionArray[i].getDConst();
        double length = sqrt(sum);
        if (op == EOpLength)
            newConstArray[0].setDConst(length);
        else {
            for (int i = 0; i < objectSize; i++)
                newConstArray[i].setDConst(unionArray[i].getDConst() / length);
        }
        break;
    }

    // TODO: 3.0 Functionality: unary constant folding: the rest of the ops have to be fleshed out

    case EOpPackSnorm2x16:
    case EOpPackUnorm2x16:
    case EOpPackHalf2x16:

    case EOpUnpackSnorm2x16:
    case EOpUnpackUnorm2x16:
    case EOpUnpackHalf2x16:

    case EOpDeterminant:
    case EOpMatrixInverse:
    case EOpTranspose:

    case EOpAny:
    case EOpAll:
        return 0;
    
    default:
        assert(componentWise);
        break;
    }

    // Turn off the componentwise loop
    if (! componentWise)
        objectSize = 0;

    // Process component-wise operations
    for (int i = 0; i < objectSize; i++) {
        switch (op) {
        case EOpNegative:
            switch (getType().getBasicType()) {
            case EbtDouble:
            case EbtFloat: newConstArray[i].setDConst(-unionArray[i].getDConst()); break;
            case EbtInt:   newConstArray[i].setIConst(-unionArray[i].getIConst()); break;
            case EbtUint:  newConstArray[i].setUConst(static_cast<unsigned int>(-static_cast<int>(unionArray[i].getUConst())));  break;
            default:
                return 0;
            }
            break;
        case EOpLogicalNot:
        case EOpVectorLogicalNot:
            switch (getType().getBasicType()) {
            case EbtBool:  newConstArray[i].setBConst(!unionArray[i].getBConst()); break;
            default:
                return 0;
            }
            break;
        case EOpBitwiseNot:
            newConstArray[i] = ~unionArray[i];
            break;
        case EOpRadians:
            newConstArray[i].setDConst(unionArray[i].getDConst() * pi / 180.0);
            break;
        case EOpDegrees:
            newConstArray[i].setDConst(unionArray[i].getDConst() * 180.0 / pi);
            break;
        case EOpSin:
            newConstArray[i].setDConst(sin(unionArray[i].getDConst()));
            break;
        case EOpCos:
            newConstArray[i].setDConst(cos(unionArray[i].getDConst()));
            break;
        case EOpTan:
            newConstArray[i].setDConst(tan(unionArray[i].getDConst()));
            break;
        case EOpAsin:
            newConstArray[i].setDConst(asin(unionArray[i].getDConst()));
            break;
        case EOpAcos:
            newConstArray[i].setDConst(acos(unionArray[i].getDConst()));
            break;
        case EOpAtan:
            newConstArray[i].setDConst(atan(unionArray[i].getDConst()));
            break;

        case EOpDPdx:
        case EOpDPdy:
        case EOpFwidth:
        case EOpDPdxFine:
        case EOpDPdyFine:
        case EOpFwidthFine:
        case EOpDPdxCoarse:
        case EOpDPdyCoarse:
        case EOpFwidthCoarse:
            // The derivatives are all mandated to create a constant 0.
            newConstArray[i].setDConst(0.0);
            break;

        case EOpExp:
            newConstArray[i].setDConst(exp(unionArray[i].getDConst()));
            break;
        case EOpLog:
            newConstArray[i].setDConst(log(unionArray[i].getDConst()));
            break;
        case EOpExp2:
            {
                const double inv_log2_e = 0.69314718055994530941723212145818;
                newConstArray[i].setDConst(exp(unionArray[i].getDConst() * inv_log2_e));
                break;
            }
        case EOpLog2:
            {
                const double log2_e = 1.4426950408889634073599246810019;
                newConstArray[i].setDConst(log2_e * log(unionArray[i].getDConst()));
                break;
            }
        case EOpSqrt:
            newConstArray[i].setDConst(sqrt(unionArray[i].getDConst()));
            break;
        case EOpInverseSqrt:
            newConstArray[i].setDConst(1.0 / sqrt(unionArray[i].getDConst()));
            break;

        case EOpAbs:
            if (unionArray[i].getType() == EbtDouble)
                newConstArray[i].setDConst(fabs(unionArray[i].getDConst()));
            else if (unionArray[i].getType() == EbtInt)
                newConstArray[i].setIConst(abs(unionArray[i].getIConst()));
            else
                newConstArray[i] = unionArray[i];
            break;
        case EOpSign:
            #define SIGN(X) (X == 0 ? 0 : (X < 0 ? -1 : 1))
            if (unionArray[i].getType() == EbtDouble)
                newConstArray[i].setDConst(SIGN(unionArray[i].getDConst()));
            else
                newConstArray[i].setIConst(SIGN(unionArray[i].getIConst()));
            break;
        case EOpFloor:
            newConstArray[i].setDConst(floor(unionArray[i].getDConst()));
            break;
        case EOpTrunc:
            if (unionArray[i].getDConst() > 0)
                newConstArray[i].setDConst(floor(unionArray[i].getDConst()));
            else
                newConstArray[i].setDConst(ceil(unionArray[i].getDConst()));
            break;
        case EOpRound:
            newConstArray[i].setDConst(floor(0.5 + unionArray[i].getDConst()));
            break;
        case EOpRoundEven:
        {
            double flr = floor(unionArray[i].getDConst());
            bool even = flr / 2.0 == floor(flr / 2.0);
            double rounded = even ? ceil(unionArray[i].getDConst() - 0.5) : floor(unionArray[i].getDConst() + 0.5);
            newConstArray[i].setDConst(rounded);
            break;
        }
        case EOpCeil:
            newConstArray[i].setDConst(ceil(unionArray[i].getDConst()));
            break;
        case EOpFract:
        {
            double x = unionArray[i].getDConst();
            newConstArray[i].setDConst(x - floor(x));
            break;
        }

        case EOpIsNan:
        {
            newConstArray[i].setBConst(isNan(unionArray[i].getDConst()));
            break;
        }
        case EOpIsInf:
        {
            newConstArray[i].setBConst(isInf(unionArray[i].getDConst()));
            break;
        }

        // TODO: 3.0 Functionality: unary constant folding: the rest of the ops have to be fleshed out

        case EOpSinh:
        case EOpCosh:
        case EOpTanh:
        case EOpAsinh:
        case EOpAcosh:
        case EOpAtanh:

        case EOpFloatBitsToInt:
        case EOpFloatBitsToUint:
        case EOpIntBitsToFloat:
        case EOpUintBitsToFloat:

        default:
            return 0;
        }
    }

    TIntermConstantUnion *newNode = new TIntermConstantUnion(newConstArray, returnType);
    newNode->getWritableType().getQualifier().storage = EvqConst;
    newNode->setLoc(getLoc());

    return newNode;
}