#include <iostream>
#include "CalculatingValues.h"
#include "IProbabilisticSimplicityTest.h"
#include <vector>
#include <random>


unsigned int isPrime(unsigned int bitlength) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1 << (bitlength - 1), (1 << bitlength) - 1);        //для защиты Ферма
    return dis(gen);
}


unsigned int GeneratePrimeNumber(unsigned int bitlength, char numberTest) {

    FermatTest* obj1 = nullptr;
    SolovayStrassenTest* obj2 = nullptr;
    MillerRabinTest* obj3 = nullptr;
    unsigned int prime;

    switch (numberTest){
    case '1': {
        obj1 = new FermatTest();
        
        do{
            prime = isPrime(bitlength);
        } 
        while (!obj1->iteration(prime));
        return prime;
    }
    case '2': {
        obj2 = new SolovayStrassenTest();

        do {
            prime = isPrime(bitlength);
        } while (!obj2->iteration(prime));
        return prime;
    }
    case '3': {
        obj3 = new MillerRabinTest();

        do {
            prime = isPrime(bitlength);
        } while (!obj3->iteration(prime));
        return prime;
    }
    default:
        return 0;
    }

    delete obj1;
    delete obj2;
    delete obj3;
}

unsigned int multiplicativeInverse(unsigned int e, unsigned int phi) {
    long long x = 0, y = 1, lastx = 1, lasty = 0, temp;
    while (phi != 0) {
        unsigned int quotient = e / phi;
        temp = e;
        e = phi;
        phi = temp % phi;

        temp = x;
        x = lastx - quotient * x;
        lastx = temp;

        temp = y;
        y = lasty - quotient * y;
        lasty = temp;
    }
    if (lastx < 0) lastx += phi;
    return lastx;
}

class KeyGeneration {
private:
    unsigned int _bitLength;
    char _test_selection;

public:
    KeyGeneration(unsigned int bitLength, char test_selection) {
        this->_bitLength = bitLength;
        this->_test_selection = test_selection;
    }

    void generate() {
        unsigned int p = GeneratePrimeNumber(_bitLength, _test_selection);
        unsigned int q = GeneratePrimeNumber(_bitLength, _test_selection);
        unsigned int e = 65537;      //экспонента для защиты от атаки Винера
        unsigned int n = p * q;
        unsigned int phi = (p - 1) * (q - 1);

        if (e < 1 || e > phi) throw std::runtime_error("Ошибка!\tВозможно, вы ввели слишком маленькую длину бита");

        unsigned int d = multiplicativeInverse(e, phi);

        if (p == 0 || q == 0) throw std::runtime_error("Ошибка!\tВозможно, вы ввели неверное значение");

        std::cout << "Созданные ключи: " << p << ", " << q << "\n";
        std::cout << "Открытый ключ: (" << e << ", " << n << ")\n";
        std::cout << "Закрытый ключ: (" << d << ", " << n << ")\n";
    }
};




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
    std::cout << "Символ Якоби для чисел " << a << " и " << n << " равен " << test.jacobi(a, n) << std::endl << std::endl;


    FermatTest fermaTest;
    std::vector<int> testCase = { 5, 6, 7, 8, 9, 10, 11, 561 };
    /*for (int test : testCase) {
        std::cout << "Тест " << test << "...\n";
        bool isPrime = fermaTest.runTest(test, 0.5);
        std::cout << "Результат: " << (isPrime ? "prime" : "composite") << "\n\n";
    }*/

    SolovayStrassenTest solovayStrassenTest;
    /*for (int test : testCase) {
        std::cout << "Тест " << test << "...\n";
        bool isPrime = solovayStrassenTest.runTest(test, 0.5);
        std::cout << "Результат: " << (isPrime ? "prime" : "composite") << "\n\n";
    }*/

    MillerRabinTest millerRabinTest;
    /*for (int test : testCase) {
        std::cout << "Тест " << test << "...\n";
        bool isPrime = millerRabinTest.runTest(test, 0.5);
        std::cout << "Результат: " << (isPrime ? "prime" : "composite") << "\n\n";
    }*/




    //СДЕЛАТЬ ВВОД С КОНСОЛИ ДЛЯ ВЫБОРА ТЕСТА ПРОСТОТЫ ФЕРМА, СОЛОВЕЯ И МЕЛЛИЕРА (1, 2 И 3 СООТВЕТСТВЕННО)
    std::cout << "Выберите, какой тест простоты вы хотите использовать:\n1.Test Fermat\n2.Test Solovay-Strassen\n3.Test Miller-Rabin\n";
    char value;
    std::cin >> value;

    KeyGeneration kg(16, value);
    kg.generate();

    return 0;
}
