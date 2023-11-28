#include <vector>
#include <iostream>
#include <utility>
#include <math.h>
#include <string>

#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <chrono>

#include <iostream>
using namespace std;
// Вывод системы уравнений

void sysout(double **a, double *y, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << a[i][j] << "*x" << j;
            if (j < n - 1)
                cout << " + ";
        }
        cout << " = " << y[i] << endl;
    }
    return;
}
double *gauss(double **matrix, double *y_vector, int size)
{
    double *x, max;
    int k, index;
    const double eps = 0.00001; // точность
    x = new double[size];
    k = 0;
    while (k < size)
    {
        // Поиск строки с максимальным a[i][k]
        max = abs(matrix[k][k]);
        index = k;
        for (int i = k + 1; i < size; i++)
        {
            if (abs(matrix[i][k]) > max)
            {
                max = abs(matrix[i][k]);
                index = i;
            }
        }
        // Перестановка строк
        if (max < eps)
        {
            cout << "Решение получить невозможно из-за нулевого столбца ";
            cout << index << " матрицы A" << endl;
            return 0;
        }
        for (int j = 0; j < size; j++)
        {
            double temp = matrix[k][j];
            matrix[k][j] = matrix[index][j];
            matrix[index][j] = temp;
        }
        double temp = y_vector[k];
        y_vector[k] = y_vector[index];
        y_vector[index] = temp;
        // Нормализация уравнений
        for (int i = k; i < size; i++) // Каждый ряд матрицы мы делим на ведущий элемент
        {
            double temp = matrix[i][k];
            if (abs(temp) < eps)
                continue; // для нулевого коэффициента пропустить
            for (int j = k; j < size; j++)
            {
                matrix[i][j] = matrix[i][j] / temp;
            }
            y_vector[i] = y_vector[i] / temp;
            if (i == k)
                continue; // уравнение не вычитать само из себя
            for (int j = k; j < size; j++)
            {
                matrix[i][j] = matrix[i][j] - matrix[k][j];
            }
            y_vector[i] = y_vector[i] - y_vector[k];
        }
        k++;
    }
    // обратная подстановка
    for (k = size - 1; k >= 0; k--)
    {
        x[k] = y_vector[k];
        for (int i = 0; i < k; i++)
            y_vector[i] = y_vector[i] - matrix[i][k] * x[k];
    }
    return x;
}
int main()
{
    
    // double **matrix, *y_vector, *x;
    // int size;
    // std::cout << "Введите количество уравнений: ";
    // std::cin >> size;
    // matrix = new double *[size];
    // y_vector = new double[size];
    // for (int i = 0; i < size; i++)
    // {
    //     matrix[i] = new double[size];
    //     for (int j = 0; j < size; j++)
    //     {
    //         std::cout << "a[" << i << "][" << j << "]= ";
    //         std::cin >> matrix[i][j];
    //     }
    // }
    // for (int i = 0; i < size; i++)
    // {
    //     std::cout << "y[" << i << "]= ";
    //     std::cin >> y_vector[i];
    // }

    int size;
    std::cout << "Введите размер массива: ";
    std::cin >> size;
    std::cout << std::endl;
    double **matrix;
    double *y_vector;
    double *x;
    
    y_vector = new double[size];
    matrix = new double *[size];

    for(int i = 0; i < size; i++)
    {
        matrix[i] = new double[size];
        for(int j = 0; j < size; j++){
            if(i == j){
                // std::cout << "a["<< i <<"]["<< j <<"] = ";
                // std:: cin >> matrix[i][j];
                matrix[i][j] = rand() % (50000 - (-50000) + 1) + (-50000);
            }
            else {
                matrix[i][j] = 0;
            }

        }
    }

    for (int i = 0; i < size; i++)
    {
        // std::cout << "y[" << i << "]= ";
        // std::cin >> y_vector[i];
        y_vector[i] = rand() % (50000 - (-50000) + 1) + (-50000);
    }

    //sysout(matrix, y_vector, size);
    std::cout << std::endl;


    auto start = std::chrono::high_resolution_clock::now();
    
    x = gauss(matrix, y_vector, size);
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;

    // for (int i = 0; i < size; i++)
    //     std::cout << "x[" << i << "]=" << x[i] << std::endl;

    return 0;
}