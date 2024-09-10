void TAnimContainer::PrepareModel()
{ // tutaj zostawi� tylko ustawienie submodelu, przeliczanie ma by� w UpdateModel()
    if (pSubModel) // pozby� si� tego - sprawdza� wcze�niej
    {
        // nanoszenie animacji na wzorzec
        if (iAnim & 1) // zmieniona pozycja wzgl�dem pocz�tkowej
            pSubModel->SetRotateXYZ(vRotateAngles); // ustawia typ animacji
        if (iAnim & 2) // zmieniona pozycja wzgl�dem pocz�tkowej
            pSubModel->SetTranslate(vTranslation);
        if (iAnim & 4) // zmieniona pozycja wzgl�dem pocz�tkowej
        {
            if (fAngleSpeed > 0.0f)
            {
                fAngleCurrent +=
                    fAngleSpeed * Timer::GetDeltaTime(); // aktualny parametr interpolacji
                if (fAngleCurrent >= 1.0f)
                { // interpolacja zako�czona, ustawienie na pozycj� ko�cow�
                    qCurrent = qDesired;
                    fAngleSpeed = 0.0; // wy��czenie przeliczania wektora
                    if (evDone)
                        Global::AddToQuery(evDone,
                                           NULL); // wykonanie eventu informuj�cego o zako�czeniu
                }
                else
                { // obliczanie pozycji po�redniej
                    // normalizacja jest wymagana do interpolacji w nast�pnej animacji
                    qCurrent = Normalize(
                        Slerp(qStart, qDesired, fAngleCurrent)); // interpolacja sferyczna k�ta
                    // qCurrent=Slerp(qStart,qDesired,fAngleCurrent); //interpolacja sferyczna k�ta
                    if (qCurrent.w ==
                        1.0) // rozpozna� brak obrotu i wy��czy� w iAnim w takim przypadku
                        iAnim &= ~4; // k�ty s� zerowe
                }
            }
            mAnim->Quaternion(&qCurrent); // wype�nienie macierzy (wymaga normalizacji?)
            pSubModel->mAnimMatrix = mAnim; // u�yczenie do submodelu (na czas renderowania!)
        }
    }
    // if (!strcmp(pSubModel->pName,"?Z?�?^?[")) //jak g��wna ko��
    // WriteLog(AnsiString(pMovementData->iFrame)+": "+AnsiString(iAnim)+"
    // "+AnsiString(vTranslation.x)+" "+AnsiString(vTranslation.y)+" "+AnsiString(vTranslation.z));
}