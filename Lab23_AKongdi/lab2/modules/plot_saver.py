import matplotlib.pyplot as plt


def save_plot(data: list, fname: str):
    """
    Описание:
    Функция сохраняет построенный график в файл.

    Аргументы:
    - data (list): Данные для построения графика.
    - fname (str): Имя файла для сохранения графика.

    Примечание:
    Формат файла будет определен на основе расширения имени файла.
    """
    try:
        plt.plot(data)
        plt.title('График данных')
        plt.xlabel('Индекс')
        plt.ylabel('Значение')
        plt.savefig(fname)
        plt.close()
        print(f"График сохранен в файл '{fname}'.")
    except Exception as e:
        print(f"Ошибка при сохранении графика в файл '{fname}': {e}")
