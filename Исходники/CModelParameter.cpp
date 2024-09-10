// virtual
void CModelParameterSpecies::setCN(const CCopasiObjectName & cn)
{
    CModelParameter::setCN(cn);

    // Determine the CN for the compartment.
    // "CN=Root,Model=New Model,Vector=Compartments[compartment],Vector=Metabolites[A]"
    CCopasiObjectName Tmp = mCN;
    std::string Separator = "";

    for (; Tmp != ""; Tmp = Tmp.getRemainder())
    {
        CCopasiObjectName Primary = Tmp.getPrimary();
        mCompartmentCN += Separator + Primary;
        Separator = ",";

        if (Primary.getObjectType() == "Vector" &&
                Primary.getObjectName() == "Compartments")
        {
            break;
        }
    }
}