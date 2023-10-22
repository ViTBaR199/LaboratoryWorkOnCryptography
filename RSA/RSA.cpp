#include <iostream>
#include "CalculatingValues.h"
#include "IProbabilisticSimplicityTest.h"
#include "Atack.h"
#include <vector>
#include <random>


unsigned long long isPrime(uint64_t bitlength) {
    std::random_device rd;
    std::mt19937 gen(rd());

    int start = pow(10, bitlength - 1);
    int end = pow(10, bitlength) - 1;
    std::uniform_int_distribution<> dis(start, end);

    //std::uniform_int_distribution<unsigned long long> dis(1ULL << (bitlength - 1), (1ULL << bitlength) - 1);
    return dis(gen);
}


unsigned long long GeneratePrimeNumber(uint64_t bitlength, char numberTest) {

    FermatTest* obj1 = nullptr;
    SolovayStrassenTest* obj2 = nullptr;
    MillerRabinTest* obj3 = nullptr;
    unsigned long long prime;

    switch (numberTest) {
    case '1': {
        /*obj1 = new FermatTest();
        prime = isPrime(bitlength);

        if ((prime & 1) == 0) {
            prime++;
        }
        while (!obj1->iteration(prime)){
            prime += 2;
        }
        break;*/
        obj1 = new FermatTest();

        do {
            prime = isPrime(bitlength);
        } while (!obj1->iteration(prime));
        break;
    }
    case '2': {
        obj2 = new SolovayStrassenTest();

        do {
            prime = isPrime(bitlength);
        } while (!obj2->iteration(prime));
        break;
    }
    case '3': {
        obj3 = new MillerRabinTest();

        do {
            prime = isPrime(bitlength);
        } while (!obj3->iteration(prime));
        break;
    }
    default:
        return 0;
    }
    delete obj1;
    delete obj2;
    delete obj3;
    return prime;
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
//unsigned int multiplicativeInverse(unsigned int e, unsigned int phi) {
//    e = e % phi;
//    for (int i = 1; i < phi; i++) {
//        if ((e * i) % phi == 1) {
//            return i;
//        }
//    }
//    return -1;
//}


//unsigned long long ModPow(unsigned long long base, unsigned long long exp, unsigned long long mod) {
//    base %= mod;
//    unsigned long long result = 1;
//    base = base % mod;
//    while (exp > 0) {
//        if (exp & 1) {
//            result = (result * base) % mod;
//        }
//        exp = exp >> 1;
//        base = (base * base) % mod;
//    }
//    return result;
//}


unsigned long long int mul_mod(unsigned long long x, unsigned long long y, unsigned long long m) {
    if (x > y) {
        unsigned long long tmp = x;
        x = y;
        y = tmp;
    }
    unsigned long long res = 0;
    unsigned long long iy = y;
    while (x) {
        if (x & 1)
            res = (res + iy) % m;
        iy = (iy + iy) % m;
        x >>= 1;
    }
    return  res;
}

unsigned long long ModPow(unsigned long long x, unsigned long long n, unsigned long long m) {
    unsigned long long res = 1;
    while (n) {
        if (n & 1)
            res = mul_mod(res, x, m);
        x = mul_mod(x, x, m);
        n >>= 1;
    }
    return res;
}

//НОД для создания публичного ключа
unsigned int NOD(unsigned int bitlength, char numberTest, unsigned int value) {
    unsigned int a = value;
    unsigned int b = GeneratePrimeNumber(bitlength, numberTest);
    unsigned int c = b;
    if (a < c) {
        std::swap(a, c);
    }

    while (c) {
        a %= c;
        std::swap(a, c);
    }

    if (a == 1) {
        return b;
    }
    else {
        return NOD(bitlength, numberTest, a);
    }
}
//unsigned int NOD(unsigned int value1, unsigned int value2) {
//    int temp;
//    while (true) {
//        temp = value1 % value2;
//        if (temp == 0) return value2;
//        value1 = value2;
//        value2 = temp;
//    }
//}
//unsigned int extendedEuclid(unsigned int a, unsigned int b, unsigned int &x, unsigned int &y) {
//    if (a == 0) {
//        x = 0;
//        y = 1;
//        return b;
//    }
//    unsigned int x1, y1;
//    int d = extendedEuclid(b % a, a, x1, y1);
//    x = y1 - (b / a) * x1;
//    y = x1;
//    return d;
//}

//НОД
long long extended_gcd(long long a, long long b, long long& x, long long& y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    long long x1, y1;
    long long d = extended_gcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

//обратное по модулю число
long long mod_inverse(long long e, long long phi) {
    long long x, y;
    long long g = extended_gcd(e, phi, x, y);
    if (g != 1)
        throw "modular inverse does not exist";
    else {
        x = (x % phi + phi) % phi;
        return x;
    }
}

bool Fermat(long long p, long long q) {
    if (p == q) {
        return false;
    }
    unsigned long long A = (p + q) / 2;
    long long B = abs(p - q);
    unsigned long long N = (A - B) * (A + B);

    if (N < 0) {
        return true;
    }

    if (p != sqrt(N) && q != sqrt(N)) {
        return true;
    }
}

bool Wiener(unsigned long long d, unsigned long long n) {
    if (d < (0.3333 * pow((double)n, 0.25))) {
        return true;
    }
    else false;
}

class RSA {
public:
    unsigned int _bitLength;
    char _test_selection;
    unsigned long long _value_n;
    unsigned long long _pubKey;
    unsigned long long _privKey;

public:
    RSA(unsigned int bitLength, char test_selection) {
        this->_bitLength = bitLength;
        this->_test_selection = test_selection;
        this->_value_n = 0;
        this->_pubKey = 0;
        this->_privKey = 0;
    }
    void generate() {
        long long p = GeneratePrimeNumber(_bitLength, _test_selection);
        long long q = GeneratePrimeNumber(_bitLength, _test_selection);

        if (!Fermat(p, q)) {
            throw "Значения уязвимы для атаки Ферма";
        }

        this->_value_n = p * q;

        unsigned long long phi = (p - 1) * (q - 1);
        std::cout << "Созданные ключи: " << p << ", " << q << ", phi = " << phi << "\n";

        this->_pubKey = NOD(_bitLength, _test_selection, phi);      //экспонента для защиты от атаки Винера
        std::cout << "Открытый ключ: (" << _pubKey << ", " << _value_n << ")\n";

        if (_pubKey < 1 || _pubKey > phi) {
            throw "Ошибка!\tВозможно, вы ввели слишком маленькую длину бита";
        }
        
        this->_privKey = mod_inverse(_pubKey, phi);
        //this->_privKey = multiplicativeInverse(_pubKey, phi);
        if (!Wiener(_privKey, _value_n)) {
            throw "Значения уязвимы для атаки Винера";
        }

        if (p == 0 || q == 0) {
            throw "Ошибка!\tВозможно, вы ввели неверное значение";
        }

        std::cout << "Закрытый ключ: (" << _privKey << ", " << _value_n << ")\n";

    }

    unsigned long long Encrypt(unsigned long long message) {
        return ModPow(message, this->_pubKey, this->_value_n);
    }

    unsigned long long Decrypt(unsigned long long messege) {
        return ModPow(messege, this->_privKey, this->_value_n);
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

    //RSA kg(10, value);
    RSA kg(5, value);
    kg.generate();
    unsigned long long res_enc = kg.Encrypt(123454321);
    std::cout << kg.Decrypt(res_enc) << '\n';

    //Атака Ферма:
    Atack fer;
    auto res_fer = fer.AtackFermat(kg._value_n);
    std::cout << "Найденное phi с помощью открытого ключа: " << res_fer << "\n";
    std::cout << "Найденный закрытый ключ: " << mod_inverse(kg._pubKey, res_fer);

    auto res_su_fr = fer.ChainShot(kg._pubKey, kg._value_n);
    /*for (int i = 0; i < res_su_fr.size(); i++) {
        std::cout << "\nЦепная дроби: a= " << res_su_fr[i];
    }*/

    auto res_wien = fer.SuitableFractions(res_su_fr);
    for (int i = 0; i < res_wien.size(); i++) {
        std::cout << "\nПодходящие дроби: p= " << res_wien[i].first << " q= " << res_wien[i].second;
    }

    return 0;
}
