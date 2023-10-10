﻿#include <iostream>
#include "CalculatingValues.h"

int main()
{
    setlocale(0, "");
    CalculatingValues test;
    int a = 7, p = 11, n = 17;

    /*
    символ Лежандра определен только для простых чисел и целого числа a
    если значение a - квадрат какого-то числа по модолю p (например a=9 при p=11), то значение Лежандра = 1
    если значение a - не является квадратом какого-то числа по модолю p (например a = 6 при p = 11), то значение Лежандра = -1
    если значение a = 0 или a делитися на p без остатка, то значение Лежандра = 0
    */
    std::cout << "Символ Лежандра для чисел " << a << " и " << p << " равен " << test.legendre(a, p) << std::endl;


    /*
    символ Якоби обобщает символ Лежандра, определен для всех целых чисел a и всех нечетных положительных чисел n
    если значение a - квадрат какого-то числа по модолю n, то значение Якоби = 1
    если значение a - не является квадратом какого-то числа по модолю n, то значение Якоби = -1
    если а делится на n без остатка, то значение Якоби = 0
    При этом, если n - простое число, то символ Якоби совподает с символом Лагранжа
    */
    std::cout << "Символ Якоби для чисел " << a << " и " << n << " равен " << test.jacobi(a, n) << std::endl;
    return 0;
}
