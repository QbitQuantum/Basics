wstring ExceptionHelper::GetCurrentExceptionMessage()
{
    wstring exceptionMessage;
    const exception_ptr exceptionPointer = current_exception();

    if(exceptionPointer == nullptr)
    {
        return wstring();
    }

    try
    {
        rethrow_exception(exceptionPointer);
    }
    catch (const SelectedTextTranslateBaseException& exception)
    {
        exceptionMessage = exception.GetFullErrorMessage();
    }
    catch (const SelectedTextTranslateBaseException* exception)
    {
        exceptionMessage = exception->GetFullErrorMessage();
    }
    catch (const exception& exception)
    {
        exceptionMessage = StringUtilities::Format(L"\tException message: '%hs'", exception.what());
    }
    catch (...)
    {
        exceptionMessage = L"\tUnknown exception occurred.";
    }

    return exceptionMessage;
}