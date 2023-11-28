#include <vector>
#include <iostream>
#include <utility>
#include <math.h>
#include <string>
#include <stdlib.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <chrono>

void sysout(double **a, double *y, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cout << a[i][j] << "*x" << j;
            if (j < n - 1)
                std::cout << " + ";
        }
        std::cout << " = " << y[i] << std::endl;
    }
    return;
}



int main(){
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

    sysout(matrix, y_vector, size);
    return 0;
}