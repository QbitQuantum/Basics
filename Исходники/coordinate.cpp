/*************************************************************************

                 ЗАГРУЗКА ОПИСАНИЯ ИЗ ТЕКСТОВОГО ФАЙЛА

  1. Общий формат:

     1.1 Заголовок

     enum имя, синоним1, синоним2, ...

     Кроме основного имени можно устанавливать альтернативные имена
     координаты (синонимы). Это необходимо для работы с некоторыми
     просторечными конструкциями (типа слова 'ЕГОННЫЙ'). Имя координаты
     должно начинаться с буквы или символа '_'.

     1.2 Список состояний (два взаимоисключающих случая):

     ... = имя_источника

     - таким способом координата [имя] получает тот же список состояний,
       что и заявленые для [имя_источник].

     ... { сост1 сост2 ... состN }

     - в фигурных скобочках перечисляются имена состояний.

  2. Один из особых случаев - координаты с двумя состояниями,
     представимыми по смыслу как TRUE и FALSE. Формат описани
     их несколько иной. Объявление имеет такой формат:

                 :

     enum имя_координаты

                 :


     То есть имена состояний явно не объявляются. Внутреннее описание
     также не загружается подставными именами состояний, но при операциях
     с координатами появление координаты с нулевым количеством состояний
     отлавливается и особо учитывается.
**************************************************************************/
void GramCoord::LoadTxt(
    Macro_Parser &txtfile,
    const Grammar& gram,
    bool IsRealized
)
{
    is_realized = IsRealized;

    BethToken coord_name = txtfile.read();
    sol_check_coord_name(gram.GetDict(), txtfile, coord_name);
    name.push_back(coord_name.c_str());

    const bool Me = gram.GetDict().GetDebugLevel_ir() >= 3;
    if (Me)
    {
        // Эхо-сообщение: начали трансляцию координаты.
        gram.GetIO().mecho().printf(
            "%us [%vfE%us%vn]->",
            sol_get_token(B_COORDINATE).c_str(),
            name.get(0).c_str()
        );
    }


    BSourceState back = txtfile.tellp();

    bool cname_loaded = false;
    if (txtfile.read().GetToken() == B_AS)
    {
        c_name = txtfile.read();
        back = txtfile.tellp();
        cname_loaded = true;
    }
    else
        txtfile.seekp(back);

    // Цикл загрузки компонентов описания координаты.
    bool loading = true;
    while (loading)
    {
        const BethToken t1 = txtfile.read();

        switch (t1.GetToken())
        {
        case B_EQUAL:
        {
            // Встретили спецификацию '='. Так что пересылаем себе состояния
            // другой координаты, имя которой идёт следом.

            const BethToken another = txtfile.read();
            const GramCoordAdr ianother = gram.FindCoord(another.string());

            if (ianother.GetIndex() == UNKNOWN)
            {
                Print_Error(another, txtfile);
                MemFormatter f;
                f.printf(
                    "The coordinate [%us] is not previously "
                    "declared in grammar\n"
                    , another.c_str()
                );
                throw E_Solarix(f.string().c_str());
            }

            state = gram.coords()[ianother.GetIndex()].state; // Пересылаем себе состояния

#if defined SOL_COMPILER  
// Очищаем C-имена состояний
            for (lem::Container::size_type i = 0; i < state.size(); ++i)
            {
                state[i].Clear_API_Names();
            }
#endif

            loading = false; // Больше считывать нечего
            break;
        }

        case B_COMMA:
        {
            // Через запятую идут синонимы имени координаты.
            const BethToken t2 = txtfile.read();
            sol_check_s_name(gram.GetDict(), txtfile, t2, true);
            if (name.Find(t2.c_str()) != UNKNOWN)
            {
                Print_Error(t2, txtfile);
                MemFormatter f;
                f.printf("Duplication of the name in coordinate [%us] declaration\n", t2.c_str());
                throw E_Solarix(f.string().c_str());
            }

            name.push_back(t2.c_str());
            break;
        }

        case B_OFIGPAREN:
        {
            // В фигурных скобочках перечислены возможные состояния координаты.

            while (!txtfile.eof())
            {
                const BSourceState back2 = txtfile.tellp();

                // Если это '}', то список атрибутов завершен.
                if (txtfile.read().GetToken() == B_CFIGPAREN)
                    break;

                txtfile.seekp(back2);
                GramCoordState dummy;
                dummy.LoadTxt(gram.GetIO(), txtfile);

                // Нет повторных объявлений состояний?
                for (lem::Container::size_type i = 0; i < dummy.size(); i++)
                {
                    // Проверим, чтобы в загруженной подгруппе не было двух
                    // одинаковых имен.
                    for (lem::Container::size_type j = 0; j < dummy.size(); j++)
                    {
                        if (i != j)
                            if (dummy[i] == dummy[j])
                            {
                                Print_Error(txtfile);
                                MemFormatter f;
                                f.printf("Two equal names in a coordinate [%us] state subgroup\n", name.string().c_str());
                                throw E_Solarix(f.string().c_str());
                            }
                    }

                    const UCString& look_for = dummy.get(i);
                    if (FindState(look_for) != UNKNOWN)
                    {
                        Print_Error(txtfile);
                        MemFormatter f;
                        f.printf("Two states of coordinate [%us] have got the same name\n", name.string().c_str());
                        throw E_Solarix(f.string().c_str());
                    }
                }

                state.push_back(dummy);

                if (Me)
                    gram.GetIO().mecho().printf('.');
            }

            loading = false;
            break;
        }

        default:
        {
            if (states().size())
            {
                Print_Error(t1, txtfile);
                MemFormatter f;
                f.printf(
                    "Definition of the coordinate [%us] is not"
                    " identical to previous one.\n"
                    , name.string().c_str()
                );
                throw E_Solarix(f.string().c_str());
            }

            // Если это не открывающая фигурная скобочка, то имеем координату
            // с двумя состояниями TRUE и FALSE (бистабильную координату).
            txtfile.seekp(back);

            // На этом считывание описания заканчиваем.
            loading = false;
            break;
        }
        } // end of switch
    } // end of while

    if (Me)
    {
        // Эхо-сообщение: закончили трансляцию координаты.
        gram.GetIO().mecho().printf("%vfAOK%vn\n");
    }

    return;
}