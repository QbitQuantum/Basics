#include "RotateAroundAxisNode.h"

#include "../../../Math/Lower Math/Quaternion.h"


ADD_NODE_REFLECTION_DATA_CPP(RotateAroundAxisNode, Vector3f(1.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 1.0f), 0.0f)

RotateAroundAxisNode::RotateAroundAxisNode(const DataLine & toRot, const DataLine & axis, const DataLine & angle, std::string name)
    : DataNode(MakeVector(toRot, axis, angle), name)
{
}

void RotateAroundAxisNode::GetMyFunctionDeclarations(std::vector<std::string> & outDecls) const
{
    std::string rotFunc = "vec3 " + GetName() + "_rotFunc(vec3 toRot, vec3 rotAxis, float rotAmount) \n\
{                                                                                                    \n\
    float halfAng = rotAmount * 0.5f;                                                                \n\
    vec3 quatXYZ = sin(halfAng) * rotAxis;                                                           \n\
    return toRot + (2.0f * cross(quatXYZ, cross(quatXYZ, toRot) + (toRot * cos(halfAng))));          \n\
}\n";
    outDecls.insert(outDecls.end(), rotFunc);
}

void RotateAroundAxisNode::WriteMyOutputs(std::string & outCode) const
{
    outCode += "\tvec3 " + GetOutputName(0) + " = " +
                            GetName() + "_rotFunc(" + GetToRotateInput().GetValue() + ", " +
                                                  GetRotateAxisInput().GetValue() + ", " +
                                                  GetRotateAmountInput().GetValue() + ");\n";
}
