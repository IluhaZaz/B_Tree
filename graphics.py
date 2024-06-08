import numpy as np
import matplotlib.pyplot as plt

values = [0, 50000, 100000, 200000, 300000, 400000, 500000]
values = [i/1000 for i in values]

with open("insert.txt") as f:
    time = f.readline()
time = [0, 0 ,0, 0] + [int(i) for i in time.split()]

b_tree = time[::4]
set = time[1::4]
bin_tree = time[2::4]
vector = time[3::4]

plt.xlabel('Количество элементов,  тыс. шт')
plt.ylabel('Время выполнения, мс')
plt.title('Вставка')

plt.plot(values, b_tree, label = "Би дерево")
plt.plot(values, set, label = "Множество")
plt.plot(values, bin_tree, label = "Дерево поиска")
plt.plot(values, vector, label = "Вектор")
plt.legend()
plt.show()

with open("search.txt") as f:
    time = f.readline()
time = [0, 0 ,0, 0] + [int(i) for i in time.split()]

b_tree = time[::4]
set = time[1::4]
bin_tree = time[2::4]
vector = time[3::4]

plt.xlabel('Количество элементов, шт')
plt.ylabel('Время выполнения, мс')
plt.title('Поиск')

plt.plot(values, b_tree, label = "Би дерево")
plt.plot(values, set, label = "Множество")
plt.plot(values, bin_tree, label = "Дерево поиска")
plt.plot(values, vector, label = "Вектор")
plt.legend()
plt.show()

plt.xlabel('Количество элементов, шт')
plt.ylabel('Время выполнения, мс')
plt.title('Поиск')

plt.plot(values, b_tree, label = "Би дерево")
plt.plot(values, set, label = "Множество")
plt.plot(values, bin_tree, label = "Дерево поиска")
plt.legend()
plt.show()