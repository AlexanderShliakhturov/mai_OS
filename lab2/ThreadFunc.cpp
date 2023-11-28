#include <vector>
#include <utility>
#include <math.h>
#include <string>
#include <cstring>
#include <typeinfo>
#include <thread>

#include <iostream>
using namespace std;

int normalize(double **matrix, double *y_vector, int i, int k, int size, double eps)
{
    double temp = matrix[i][k];
    if (abs(temp) < eps)
        return 0; // для нулевого коэффициента пропустить
    if (i < k)
        return 0;
    for (int j = k; j < size; j++)
    {
        matrix[i][j] = matrix[i][j] / temp;
    }
    y_vector[i] = y_vector[i] / temp;
    if (i == k)
        return 0; // уравнение не вычитать само из себя
    for (int j = k; j < size; j++)
    {
        matrix[i][j] = matrix[i][j] - matrix[k][j];
    }
    y_vector[i] = y_vector[i] - y_vector[k];
    return 0;
}