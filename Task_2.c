#include <stdio.h>
#include "libs/data_structures/matrix/matrix.h"
#include <windows.h>
#include <math.h>
// Функция для нахождения минимального элемента в выделенной области
int getMinInArea(matrix m) {
 position maxPos = getMaxValuePos(m);
 int min = m.values[maxPos.rowIndex][maxPos.colIndex]; // Предполагаем, 
что минимальный элемент равен максимальному
 // Из этой позиции двигаемся вверх по столбцу до начала строки,
 // увеличивая количество выделенных элементов в каждом столбце на 1
 int count = 1;
 for (int i = maxPos.rowIndex - 1; i >= 0; i--) {
 count++;
 for (int j = maxPos.colIndex - count + 1; j <= maxPos.colIndex + 
count - 1 && j < m.nCols; j++) {
 if (j >= 0) {
 min = (m.values[i][j] < min) ? m.values[i][j] : min;
 }
 }
 }
 printf("\n");
 return min;
}
// Функция для вычисления расстояния от начала координат до точки
float getDistance(int *a, int n) {
 float distance = 0;
 for (int i = 0; i < n; i++) {
 distance += pow(a[i], 2);
 }
 return sqrt(distance);
}
10
// Функция для сортировки матрицы по неубыванию расстояний до начала
координат
void sortByDistances(matrix m) {
 insertionSortRowsMatrixByRowCriteriaF(m, getDistance);
}
int cmp_long_long(const void *pa, const void *pb) {
 long long a = *(const long long *)pa;
 long long b = *(const long long *)pb;
 return (a > b) - (a < b);
}
int countNUnique(long long *a, int n) {
 if (n <= 0) return 0;
 int unique = 1;
 for (int i = 1; i < n; i++) {
 if (a[i] != a[i - 1]) {
 unique++;
 }
 }
 return unique;
}
int countEqClassesByRowsSum(matrix m) {
 // Создание массива для хранения сумм строк
 long long *rowSums = (long long *)malloc(m.nRows * sizeof(long long));
 // Вычисление сумм строк
 for (int i = 0; i < m.nRows; i++) {
 rowSums[i] = 0;
 for (int j = 0; j < m.nCols; j++) {
 rowSums[i] += m.values[i][j];
 }
 }
 // Сортировка сумм строк
 qsort(rowSums, m.nRows, sizeof(long long), cmp_long_long);
 // Подсчет уникальных сумм строк
 int uniqueSums = countNUnique(rowSums, m.nRows);
 // Освобождение памяти
 free(rowSums);
 return uniqueSums;
}
// Функция для определения количества "особых" элементов матрицы
int getNSpecialElement(matrix m) {
 int nRows = m.nRows;
 int nCols = m.nCols;
 int count = 0;
 // Проходим по каждому столбцу матрицы
 for (int j = 0; j < nCols; j++) {
 int sum = 0;
 int maxElement = m.values[0][j]; // Предполагаем, что максимальный
элемент равен первому элементу столбца
 // Вычисляем сумму элементов столбца и находим максимальный элемент
 for (int i = 0; i < nRows; i++) {
 sum += m.values[i][j];
11
 if (m.values[i][j] > maxElement) {
 maxElement = m.values[i][j];
 }
 }
 // Проверяем, является ли максимальный элемент "особым"
 if (maxElement > sum - maxElement) {
 count++;
 }
 }
 return count;
}
// Функция для поиска позиции первого минимального элемента в матрице в ее
первом столбце
position getLeftMin(matrix m) {
 int min = m.values[0][0]; // Предполагаем, что первый элемент -
минимальный
 position minPos = {0, 0}; // Позиция минимального элемента
 for (int i = 0; i < m.nRows; i++) {
 if (m.values[i][0] < min) {
 min = m.values[i][0];
 minPos.rowIndex = i;
 }
 }
 return minPos;
}
// Функция для обмена предпоследней строки с найденным столбцом
void swapPenultimateRow(matrix m, int n) {
 // Находим позицию первого минимального элемента в первом столбце
 position minPos = getLeftMin(m);
 // Обмен предпоследней строки с столбцом, в котором находится минимальный
элемент
 for (int i = 0; i < m.nCols; i++) {
 int temp = m.values[m.nRows - 2][i];
 m.values[m.nRows - 2][i] = m.values[minPos.rowIndex][i];
 m.values[minPos.rowIndex][i] = temp;
 }
}
// Функция для проверки того, что массив упорядочен по неубыванию
bool isNonDescendingSorted(int *a, int n) {
 for (int i = 1; i < n; i++) {
 if (a[i] < a[i - 1]) {
 return false;
 }
 }
 return true;
}
// Функция для проверки того, что все строки матрицы упорядочены по
неубыванию
bool hasAllNonDescendingRows(matrix m) {
 for (int i = 0; i < m.nRows; i++) {
 if (!isNonDescendingSorted(m.values[i], m.nCols)) {
 return false;
 }
 }
12
 return true;
}
// Функция для подсчета числа нулевых строк в матрице
int count_ZeroRows(matrix m) {
 int count = 0;
 for (int i = 0; i < m.nRows; i++) {
 bool isZeroRow = true;
 for (int j = 0; j < m.nCols; j++) {
 if (m.values[i][j] != 0) {
 isZeroRow = false;
break;
 }
 }
 if (isZeroRow) {
 count++;
 }
 }
 return count;
}
// Функция для поиска максимального числа нулевых строк в массиве матриц
int findMaxZeroRows(matrix *ms, int nMatrix) {
 int maxZeroRows = 0;
 for (int i = 0; i < nMatrix; i++) {
 int zeroRows = count_ZeroRows(ms[i]);
 if (zeroRows > maxZeroRows) {
 maxZeroRows = zeroRows;
 }
 }
 return maxZeroRows;
}
// Функция для вывода матриц с максимальным числом нулевых строк
void printMatrixWithMaxZeroRows(matrix *ms, int nMatrix) {
 int maxZeroRows = findMaxZeroRows(ms, nMatrix);
 printf("Матрицы с наибольшим числом нулевых строк:\n");
 for (int i = 0; i < nMatrix; i++) {
 if (count_ZeroRows(ms[i]) == maxZeroRows) {
 outputMatrix(ms[i]);
 }
 }
}
int main() {
 SetConsoleOutputCP(CP_UTF8);
 // Создаем и заполняем матрицу
 matrix m = createMatrixFromArray((const int[]){
 10, 7, 5, 6,
 3, 11, 8, 9,
 4, 1, 12, 2
 }, 3, 4);
 //Задание 8: Найти минимальный элемент матрицы в выделенной области:
 int min = getMinInArea(m);
 printf("Минимальный элемент в выделенной области: %d\n", min);
 // Освобождение памяти от матрицы
 freeMemMatrix(&m);
 // Создание матрицы с точками (пример)
 matrix points = createMatrixFromArray((const int[]){
 5, 2, 7,
 4, 1, 6,
13
 3, 8, 9
 }, 3, 3);
 // Задание 9: Сортировка точек по расстояниям до начала координат
 sortByDistances(points);
 // Вывод отсортированных точек
 printf("Точки, отсортированные по расстояниям до начала координат:\n");
 outputMatrix(points);
 // Освобождение памяти от матрицы
 freeMemMatrix(&points);
 // Создаем матрицу из примера
 matrix new = createMatrixFromArray((const int[]){
 7, 1,
 2, 7,
 5, 4,
 4, 3,
 1, 6,
 8, 0
 }, 6, 2);
 // Задание 10: Подсчитываем количество классов эквивалентных строк
 int classes = countEqClassesByRowsSum(new);
 // Выводим результат
 printf("Количество классов эквивалентных строк: %d\n", classes);
 // Освобождаем память, выделенную для матрицы
 freeMemMatrix(&new);
 // Создаем матрицу (пример)
 matrix exampleMatrix = createMatrixFromArray((const int[]){
 3, 5, 5, 4,
 2, 3, 6, 7,
 12, 2, 1, 2
 }, 3, 4);
 //Задание 11: Определяем количество "особых" элементов матрицы
 int specialElements = getNSpecialElement(exampleMatrix);
 // Выводим результат
 printf("Количество \"особых\" элементов матрицы: %d\n", specialElements);
 // Освобождаем память, выделенную для матрицы
 freeMemMatrix(&exampleMatrix);
 // Создаем и заполняем квадратную матрицу (пример)
 matrix M = createMatrixFromArray((const int[]){
 1, 2, 3,
 4, 5, 6,
 7, 8, 9
 }, 3, 3);
 // Выводим исходную матрицу
 printf("Исходная матрица:\n");
 outputMatrix(M);
 printf("\n");
 //Задание 12: Заменяем предпоследнюю строку матрицы первым из столбцов, в
котором находится минимальный элемент
 swapPenultimateRow(M, m.nCols);
14
 // Выводим результат
 printf("Матрица после замены предпоследней строки:\n");
 outputMatrix(M);
 // Освобождаем память, выделенную для матрицы
 freeMemMatrix(&M);
 // Создаем и заполняем массив матриц одного размера (пример)
 matrix *matrices = createArrayOfMatrixFromArray((const int[]){
 // Матрица 1 (неподходящая)
 1, 2, 3,
 7, 5, 6,
 4, 8, 9,
 // Матрица 2 (подходящая)
 1, 2, 3,
 4, 5, 6,
 7, 8, 9,
 // Матрица 3 (подходящая)
 1, 4, 7,
 2, 5, 8,
 3, 6, 9
 }, 3, 3, 3);
 //Задание 13: Выводим результат для каждой матрицы
 for (int i = 0; i < 3; i++) {
 printf("Матрица %d: %s\n", i + 1, 
hasAllNonDescendingRows(matrices[i]) ? "упорядочена по неубыванию" : "не
упорядочена по неубыванию");
 }
 // Освобождаем память, выделенную для массива матриц
 freeMemMatrices(matrices, 3);
 // Пример массива целочисленных матриц
 matrix matrices_new[] = {
 createMatrixFromArray((const int[]){
 0, 1, 1,
 1, 0, 0,
 0, 0, 0
 }, 3, 3),
 createMatrixFromArray((const int[]){
 1, 1, 2,
 1, 1, 1,
 4, 7, 0
 }, 3, 3),
 createMatrixFromArray((const int[]){
 0, 0, 0,
 0, 1, 0,
 0, 2, 0
 }, 3, 3),
 createMatrixFromArray((const int[]){
 0, 0, 0,
 0, 1, 0,
 0, 3, 0
 }, 3, 3)
 };
 // Вывод матриц с максимальным числом нулевых строк
 printMatrixWithMaxZeroRows(matrices_new, sizeof(matrices_new) / 
sizeof(matrices_new[0]));
15
 // Освобождение памяти, выделенной для матриц
 for (int i = 0; i < sizeof(matrices_new) / sizeof(matrices_new[0]); i++) 
{
 freeMemMatrix(&matrices_new[i]);
 }
 return 0;
}