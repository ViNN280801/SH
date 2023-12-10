# Импорт инструмента, позволяющего создавать директории
from os import mkdir

# Импорт всех написанных модулей
from modules.array_generator import generate_random_array
from modules.data_loader import load_data_from_file
from modules.data_saver import save_sorted_data_to_file
from modules.plot_saver import save_plot
from modules.plotter import plot_sorted_data
from modules.selection_sort import selection_sort

# Заполнение листов данными
data1 = load_data_from_file('datasets/dataset1.txt')
data2 = load_data_from_file('datasets/dataset2.txt')
data3 = load_data_from_file('datasets/dataset3.txt')
data4 = generate_random_array(100, 1, 50)
data5 = generate_random_array(100, 2, 102)
data6 = generate_random_array(100, -101, -17)

# Сортировка каждого листа
selection_sort(data1)
selection_sort(data2)
selection_sort(data3)
selection_sort(data4)
selection_sort(data5)
selection_sort(data6)

# Создание директории для хранения в ней отсортированных массивов
mkdir('sorted/')

# Сохранение отсортированных массивов в выходные файлы
save_sorted_data_to_file('sorted/sorted_data1.txt', data1)
save_sorted_data_to_file('sorted/sorted_data2.txt', data2)
save_sorted_data_to_file('sorted/sorted_data3.txt', data3)
save_sorted_data_to_file('sorted/sorted_data4.txt', data4)
save_sorted_data_to_file('sorted/sorted_data5.txt', data5)
save_sorted_data_to_file('sorted/sorted_data6.txt', data6)

# Построение графиков отсортированных массивов
plot_sorted_data(data1)
plot_sorted_data(data2)
plot_sorted_data(data3)
plot_sorted_data(data4)
plot_sorted_data(data5)
plot_sorted_data(data6)

# Создание директории для хранения в ней графиков
mkdir('imgs/')

# Сохранение графиков как картинки
save_plot(data1, 'imgs/plot_data1.png')
save_plot(data2, 'imgs/plot_data2.png')
save_plot(data3, 'imgs/plot_data3.png')
save_plot(data4, 'imgs/plot_data4.png')
save_plot(data5, 'imgs/plot_data5.png')
save_plot(data6, 'imgs/plot_data6.png')
