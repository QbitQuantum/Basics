/*********************************************************************
   Этот метод вызывается объектом класса Automaton при чтении секции
 automat gg {...} из текстового файла Словаря.

   Нас просят определить, должен ли структурный элемент в исходном
 текстовом файле Словаря, с начальным токеном t, загружаться нашим
 классом. В этом случае мы загружаем и возвращаем true, в противном
 случае возвращаем false. Так как мы перегрузили этот метод у
 родительского класса Grammar, "вручную" вызываем и его метод, чтобы
 Grammar мог загрузить общие для любой грамматики элементы Словаря.

   Графическая Грамматика - самая простая из всех автоматов Системы.
 В текстовом файле Словаря она описывается как набор статей, кажда
 статья есть множество представлений (отличающихся кодом) одной буквы
 Алфавита, например: большие и малые. Кроме того, Грамматика загружает
 Калибраторы. Каждый Калибратор определяет относительную частоту
 использования буквы в реальных текстах. С помошью калибраторов можно
 оптимизировать поиск символа в Алфавите, так как наиболее часто
 используемые символы будут размещены в просмотровой таблице сзади,
 и будут быстрее отыскиваться, без лишнего просмотра редких букв (поиск
 всегда будет идти с конца).
**********************************************************************/
bool GraphGram::ProcessLexem(
    const BethToken &t,
    Macro_Parser& txt,
    const Binarization_Options &options
)
{
    if (t.GetToken() == B_ALPHABET)
    {
        alphabet->LoadTxt(txt, GetDict());
        return true;
    }
    else if (t.string().eqi(L"syllab_rule"))
    {
        SyllabRule *rule = new SyllabRule();
        rule->LoadTxt(txt, GetDict());
        rule->Store(storage);
        return true;
    }
    else if (t.string().eqi(L"operation"))
    {
        GG_CharOperation *x = new GG_CharOperation();
        x->LoadTxt(txt, GetDict());
        const int id = storage->FindCharOperation(x->GetName());
        if (id != UNKNOWN)
        {
            lem::Iridium::Print_Error(t, txt);
            dict->GetIO().merr().printf("Character operation %us is already declared\n", x->GetName().c_str());
            throw lem::E_BaseException();
        }

        storage->StoreCharOperation(x);
        delete x;
        return true;
    }

    // С остальными элементами пусть разбирается базовый класс Грамматики.
    return Grammar::ProcessLexem(t, txt, options);
}