import re
from enum import IntEnum
from typing import Type


class Sign(IntEnum):
    Tonality = 1
    PurposeOfStatement = 2


TonalityItem = {
    ("Хороший", "Милый", "Заботливый") : "Дружелюбное предложение",
    ("Плохой", "Мерзкий", "Гадкий") : "Негативное предложение",
}

PurposeOfStatementItem = {
    ("?") : "Вопросительное предложение",
    ("!") : "Восклицательное предложение",
    (".") : "Повествовательное предложение"
}

def get_type_Sign(enum_type: Type[IntEnum], member_name: str):
    match enum_type[member_name].value:
        case 1:
            return TonalityItem
        case 2:
            return PurposeOfStatementItem
        case _:
            EmptyItem = []
            return EmptyItem


def get_regular_expression(enum_type: Type[IntEnum], member_name: str):
    match enum_type[member_name].value:
        case 1:
            return ""
        case _:
            return ""


text = "Этот человек ведёт себя крайне плохо"


def processing(text, item, regular_expression):
    words = text.split()
    pattern = re.compile(regular_expression, re.IGNORECASE)

    for word in words:
        if pattern.fullmatch(word):
            for key, value in item.items():
                if word in key:
                    return value
            return "Поиск по типу не удался"
    return "Тип поиска не определен"


result = processing(text, get_type_Sign(Sign, "Tonality"), get_regular_expression(Sign, "Tonality"))
print(result)