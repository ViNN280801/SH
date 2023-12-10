import matplotlib.pyplot as plt


def plot_sorted_data(sorted_data: list):
    """
    Описание:
    Функция строит график для отсортированных данных.

    Аргументы:
    - sorted_data (list): Отсортированный список данных.
    """
    try:
        plt.plot(sorted_data)
        plt.title('Отсортированные данные')
        plt.xlabel('Индекс')
        plt.ylabel('Значение')
        plt.show()
    except Exception as e:
        print(f"Ошибка при построении графика: {e}")
