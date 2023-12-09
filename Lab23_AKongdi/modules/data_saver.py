def save_sorted_data_to_file(fname: str, sorted_data: list):
    """
    Описание:
    Функция сохраняет отсортированные данные в указанный файл.

    Аргументы:
    - fname (str): Имя файла, в который нужно сохранить данные.
    - sorted_data (list): Отсортированный список данных.

    Примечание:
    Если файл существует, он будет перезаписан данными.
    """
    try:
        with open(fname, 'w') as file:
            for data in sorted_data:
                file.write(str(data) + '\n')
        print(f"Отсортированные данные сохранены в файл '{fname}'.")
    except Exception as e:
        print(f"Ошибка при сохранении данных в файл '{fname}': {e}")
