# Задача №2 / Алгоритмы

## Как всё собрать?
```shell
./build.sh
```
## Как запустить?
```shell
./main
```

## Формат ввода: Такой же как в условии задачи

Первая строка: M - количество рёбер
Последующие M строк - рёбра с произвольной нумерацией городов

## Вывод:
Первая строка - кол-во городов, которые алгоритм заразил изначально
Вторая - писок городов в оригинальной нумерации

## Алгоритм применённый в решении:
Попробуем заразить вершину $i$. Пройдёмся DFS, посмотрим сколько городов заразится, и сколько городов окажутся под риском(один больной сосед). Выберем город, заражение которого приведёт к наибольшему числу каскадных заражений, а при равенстве - к большему числу городов под риском. Повторить пока не все города заражены.

## Время...
Кажется что мы видим не очень оптимальную ассимптотику - $O(n^3)$. Однако если заметить, что на каждой итерации мы выбираем наиболее "заразный" город, и заражаем его, то возможная большая длинна DFS компенсируется заражением, или частичным заражением этих вершин, что в будующем сократит их выбор при выборе стартовой. Поэтому алгоритм работает довольно быстро.

## А как на счёт тестов?
Погоняем на простых случаях:

### Треугольник:

```shell
3
1 2
2 3
1 3
```
result:
```
2
2 1 

```
Логично


### Ромб:

```shell
4
1 2
2 3
3 4
4 1

```
result:
```
2
2 4 

```
Правда


### Клика-5:

```shell
10
1 2
1 3
1 4
1 5
2 3
2 4
2 5
3 4
3 5
4 5

```
result:
```
2
2 1 

```
действительно, для любой клики достаточно 2 инфицированных городов.

### 5-угольник:

```shell
5
1 2
2 3
3 4
4 5
5 1

```
result:
```
3
2 4 1 
```
А вот для кольца - нет
