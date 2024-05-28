"""
# Обучаем модель заданное количество эпох
epochs = 1000
for epoch in range(epochs):
    model.fit(X_train, y_train, epochs=1, verbose=0)
    # Выводим информацию об эпохе
    print(f'Epoch {epoch+1}/{epochs}')

# Теперь модель обучена, и мы можем использовать ее для предсказаний
x_test = np.array([[7]], dtype=float)
prediction = model.predict(x_test)
print(f'Prediction for {x_test[0][0]} is {prediction[0][0]}')
"""
import numpy as np
import time
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Dropout
import json
import os
from keras import regularizers

def append_json_block(number, Epoch, Time, Prediction):
    # Создаем новый блок кода
    new_block = {
        str(number): str(number * number),
        "0000": {"Epoch": Epoch},
        "0001": {"Time": Time},
        "0002": {"Prediction": Prediction}
    }
    
    # Открываем файл для чтения
    with open('LoadData.json', 'r') as file:
        # Загружаем существующие данные из файла
        data = json.load(file)
    
    # Добавляем новый блок в данные
    data.append(new_block)
    
    # Открываем файл для записи, чтобы перезаписать его
    with open('LoadData.json', 'w') as file:
        # Записываем обновленные данные в файл
        json.dump(data, file, indent=4)

while True:

    # Загрузка данных из JSON файла
    with open('LoadData.json', 'r') as f:
        data = json.load(f)

    # Инициализация списков для хранения данных
    X_train_list = []
    y_train_list = []

    # Проход по данным и извлечение нужных значений
    for item in data:
        for key, value in item.items():
            if key.isdigit() and key not in ["0000", "0001", "0002"]:  # Проверка, что ключ - число и не является исключенным
                X_train_list.append([int(key)])
                y_train_list.append([int(value)])

    # Создание массивов numpy
    X_train = np.array(X_train_list, dtype=float)
    y_train = np.array(y_train_list, dtype=float)

    int_X_value = int(X_train[-1]+1)

    # Создаем модель
    model = Sequential()
    model.add(Dense(units=1, input_shape=(1,)))

    # Компилируем модель
    model.compile(optimizer='sgd', loss='mean_squared_error')

    # Замеряем время начала обучения
    start_time = time.time()

    # Обучаем модель до тех пор, пока не будет достигнут правильный ответ
    epochs = 0
    prediction = None
    loss_history = []  # Список для хранения последних 5 значений функции потерь

    while prediction is None or prediction[0][0] != (int_X_value)*(int_X_value): # *****НОВАЯ ПАРА ЗНАЧЕНИЙ +1*****
        epochs += 1
        model.fit(X_train, y_train, epochs=1, verbose=5)
        
        # Оцениваем модель на тестовых данных и получаем текущее значение функции потерь
        x_test = np.array([[(int_X_value)]], dtype=float) # *****НОВАЯ ПАРА ЗНАЧЕНИЙ +1*****
        y_test = np.array([[(int_X_value)*(int_X_value)]], dtype=float) # *****НОВАЯ ПАРА ЗНАЧЕНИЙ +1*****
        loss = model.evaluate(x_test, y_test, verbose=5)
        loss_history.append(loss)

        prediction = model.predict(x_test)
        print(f'Epoch {epochs}: Prediction for {x_test[0][0]} is {prediction[0][0]}')
        
        # Проверяем, изменилась ли функция потерь за последние 5 эпох
        if len(loss_history) > 5 and all(loss == loss_history[-5] for loss in loss_history[-5:]):
            print(f'Stopping training {epochs} epochs.')
            predictNumber = float(prediction[0][0])
            break

    # Замеряем время окончания обучения
    end_time = time.time()

    # Вычисляем время обучения
    training_time = end_time - start_time
    print(f'Correct prediction achieved after {epochs} epochs and {training_time:.2f} seconds of training.')
    append_json_block(int_X_value, epochs, training_time, predictNumber)
    os.system("cls")
