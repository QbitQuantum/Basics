void PhoneService::editPhones(int contractor, QVector<Phone> phones)
{
    QVector<Phone> oldPhones = model->getPhones(contractor);
    QVector<Phone> newPhones = phones;

    if(oldPhones != newPhones) // telefony były edytowane
    {
        for(int i = 0; i < newPhones.size(); i++)
        {
            // jeśli nie zawierają dokładnie takiego tela, to być może była edytowana tylko nazwa lub numer
            if(!oldPhones.contains(newPhones[i]))
            {
                int posAtOld = searchPhone(newPhones[i].getId(), oldPhones);
                if(posAtOld != -1)  // znaleziono telefon liscie, ale z innymi danymi, należy edytować
                {
                    model->editPhone(contractor, newPhones[i]);
                    oldPhones[posAtOld] = newPhones[i];
                }
                else
                {
                    model->addPhone(contractor, newPhones[i]);
                    oldPhones.append(newPhones[i]);
                }
            }

        }
    }
    /*
     * jeśli dodano lub edytowano telefony to oldPhones i newPhones powinny być teraz takie same
     * jeśli nie są tzn., że w nowym kontraktorze usunięto pozycje ze starej faktury
     */
    if(oldPhones != newPhones)
    {
        for(int i = 0; i < oldPhones.size(); i++)
        {
            if(!newPhones.contains(oldPhones[i]))
            {
                model->removePhone(oldPhones[i].getId());
                oldPhones.remove(i);
            }
        }
    }
}