#include "CalculatingValues.h"
#include <iostream>


int CalculatingValues::legendre(int a, int p){
	int legendre_value = 1; //a0

    for (int i = 0; i < (p - 1) / 2; i++) {
        //возведение в степень
        //каждая итерация представляет собой умножение числа само на себя по модулю p
        legendre_value = (legendre_value * a) % p;
    }

    if (legendre_value == p - 1) {
        return -1;
    }
    else {
        return legendre_value;
    }
}

int CalculatingValues::jacobi(int a, int p) {
    p = abs(p);
    int jacobi_value = 1;

    while (a != 0) {
        while (a % 2 == 0) {
            a /= 2;

            //т.к. квадраты каждого числа по модулю 8 может быть равен только 0, 1 или 4
            //=> если квадрат числа mod 8 равен 3 или 5, то это число - неквадратичный остаток
            if (p % 8 == 3 || p % 8 == 5) {
                jacobi_value = -jacobi_value;
            }
        }

        std::swap(a, p);        //по свойству (a/p) = (p/a)(-1)^[(a-1)(p-1)/4], то есть (a/p)=(p/a) с возможным именением знака

        if (a % 4 == 3 && p % 4 == 3) {        //закон квадратичной взаимности: (a/p) = -(p/a), при p = a = 3(mod4), либо (p/a) в других случаях
            jacobi_value = -jacobi_value;
        }
        a %= p;        //по свойству (a/p) = (a modp /p)
    }
    if (p == 1) {
        return jacobi_value;
    }
    else {
        return 0;
    }
}

CalculatingValues::CalculatingValues() = default;

CalculatingValues::~CalculatingValues() = default;
