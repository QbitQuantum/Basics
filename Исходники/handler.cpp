/**
 * @brief handler called while preedit updated
 *
 * @param ppd preedit string
 * @return void
 **/
void FcitxWindowHandler::updatePreedit(const IPreeditString* ppd)
{
    FcitxInstance* instance = owner->owner;
    FcitxInputState* input = FcitxInstanceGetInputState(instance);
    FcitxInputStateSetCursorPos(input, true);
    candidate_flag = true;

    const wstring& codeinput = this->owner->view->getPySegmentor()->getInputBuffer();
    WCSTOMBS(FcitxInputStateGetRawInputBuffer(input), codeinput.c_str(), MAX_USER_INPUT);
    FcitxInputStateSetRawInputBufferSize(input, strlen(FcitxInputStateGetRawInputBuffer(input)));
}