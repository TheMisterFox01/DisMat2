#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>

#define ERROR_STR "\x1b[31mERROR:\x1b[0m "
#define NUMB_MAX UINT32_MAX

using namespace std;


bool AssertMultNumb(uint32_t l, uint32_t r)
{
    if (l == 0)
        return 0;
    uint32_t maxR = NUMB_MAX / l;
    if (r <= maxR) {
        return 0;
    }
    else {
        throw (string)"Выход за пределы числа";
        return 1;
    }
}


bool AssertAddNumb(uint32_t l, uint32_t r)
{
    uint32_t maxR = NUMB_MAX - l;
    if (r <= maxR) {
        return 0;
    }
    else {
        throw (string)"Выход за пределы числа";
        return 1;
    }
}

uint32_t powNumb(uint32_t num, uint32_t deg)
{
    uint32_t result = 1;
    while (deg) {
        if (deg % 2 == 0) {
            deg /= 2;
            AssertMultNumb(num, num);
            num *= num;
        }
        else {
            deg--;
            AssertMultNumb(result, num);
            result *= num;
        }
    }

    return result;
}


uint32_t U(uint32_t m, uint32_t n)
{
    return powNumb(m, n);
}

uint32_t fact(uint32_t m, uint32_t n)
{
    if (n > m)
        return 0;

    uint32_t result = 1;
    for (uint32_t k = 0; k < n; k++) {
        AssertAddNumb(m, k);
        AssertMultNumb(result, m - k);
        result *= (m - k);
    }
    return result;
}


uint32_t A(uint32_t m, uint32_t n)
{
    return fact(m, n);
}


uint32_t P(uint32_t n)
{
    return A(n, n);
}

uint32_t C(uint32_t m, uint32_t n)
{
    if (n > m) return 0;
    if (n == 1 || m - n == 1) return m;
    if (n == m || n == 0) return 1;
    if (n > m - n) n = m - n;
    uint32_t* A = new uint32_t[n + 1];
    for (uint32_t i = 0; i <= n; i++) {
        A[i] = 1;
    }
    try {
        for (uint32_t i = 1; i <= m - n; i++) {
            for (uint32_t j = 1; j <= n; j++) {
                AssertAddNumb(A[j], A[j - 1]);
                A[j] = A[j] + A[j - 1];
            }
        }
    }
    catch (string const& str) {
        delete[] A;
        throw str;
    }

    uint32_t result = A[n];
    delete[] A;
    return result;

}


int GetArg(char& cmd, uint32_t& numb1, uint32_t& numb2)
{
    string str;
    getline(cin, str);
    size_t len = str.length();
    cmd = 0;
    numb1 = 0;
    numb2 = 0;

    stringstream stream(str);
    string word;
    vector<string> arr;
    while (stream >> word)
        arr.push_back(word);

    try {
        if (arr.size() > 0) {
            if (arr[0].length() != 1) {
                throw (string)"Неверный первый аргумент";
            }
            else {
                cmd = arr[0][0];
            }

            if (arr.size() > 1) {
                string tmp = arr[1];
                int i = 0;
                if (tmp[i] < '0' || tmp[i] > '9') {
                    if (tmp[i] == '+') {
                        i++;
                    }
                    else if (tmp[i] == '-') {
                        throw (string)"Неверный второй аргумент";
                    }
                    else {
                        throw (string)"Неверный второй аргумент";
                    }
                }
                for (int len = tmp.length(); i < len; i++) {
                    if (tmp[i] < '0' || tmp[i] > '9')
                        throw (string)"Неверный второй аргумент";
                    AssertMultNumb(numb1, 10);
                    AssertAddNumb(numb1 * 10, tmp[i] - '0');
                    numb1 = numb1 * 10 + tmp[i] - '0';
                }


                if (arr.size() > 2) {
                    string tmp = arr[2];
                    int i = 0;
                    if (tmp[i] < '0' || tmp[i] > '9') {
                        if (tmp[i] == '+') {
                            i++;
                        }
                        else if (tmp[i] == '-') {
                            throw (string)"Неверный третий аргумент";
                        }
                        else {
                            throw (string)"Неверный третий аргумент";
                        }
                    }
                    for (int len = tmp.length(); i < len; i++) {
                        if (tmp[i] < '0' || tmp[i] > '9')
                            throw (string)"Неверный третий аргумент";
                        AssertMultNumb(numb2, 10);
                        AssertAddNumb(numb2 * 10, tmp[i] - '0');
                        numb2 = numb2 * 10 + tmp[i] - '0';
                    }

                    if (arr.size() > 3) {
                        throw (string)"Превышено количество аргументов";
                    }
                    return 3;
                }
                return 2;
            }
            return 1;
        }
    }
    catch (string const& str) {
        cout << ERROR_STR << str << endl;
        return -1;
    }


    return 0;
}

uint32_t S(uint32_t m, uint32_t n)
{
    if (m == n || n == 1) {
        return 1;
    }
    if (n == 0 || n > m) {
        return 0;
    }

    uint32_t d, s;
    if (n < (m - n + 1)) {
        d = n;
        s = m - n + 1;
    }
    else {
        d = m - n + 1;
        s = n;
    }

    uint32_t* D = new uint32_t[d + 1];
    for (uint32_t i = 1; i <= d; i++) D[i] = (uint32_t)1;
    try {
        for (uint32_t i = 2; i <= s; i++)
            for (uint32_t j = 2; j <= d; j++) {
                if (d == n) {
                    AssertMultNumb(j, D[j]);
                    AssertAddNumb(D[j - 1], j * D[j]);
                    D[j] = D[j - 1] + j * D[j];
                }
                else {
                    AssertMultNumb(j, D[j - 1]);
                    AssertAddNumb(D[j], j * D[j - 1]);
                    D[j] = D[j] + j * D[j - 1];
                }
            }
    }
    catch (string const& str) {
        delete[] D;
        throw str;
    }

    uint32_t result = D[d];
    delete[] D;

    return result;
}


uint32_t B(uint32_t m)
{
    if (m == 0) {
        return 1;
    }
    uint32_t* A = new uint32_t[m + 1];

    A[1] = 1;
    uint32_t t, s;

    try {
        for (uint32_t n = 2; n <= m; n++) {
            t = A[1];
            A[1] = A[n - 1];
            for (uint32_t k = 2; k <= n; k++) {
                s = A[k];
                AssertAddNumb(A[k - 1], t);
                A[k] = A[k - 1] + t;
                t = s;
            }
        }
    }
    catch (string const& str) {
        delete[] A;
        throw str;
    }

    uint32_t result = A[m];
    delete[] A;

    return result;
}



void Help(void)
{
    cout << "Help:" << endl;
    cout << "U <m> <n>" << "\t" << "U" << endl;
    cout << "A <m> <n>" << "\t" << "A" << endl;
    cout << "P <n>" << "\t\t" << "P" << endl;
    cout << "C <m> <n>" << "\t" << "C" << endl;
    cout << "S <m> <n>" << "\t" << "Sterling's number" << endl;
    cout << "B <n>" << "\t\t" << "Bell's Number" << endl;
    cout << "H" << "\t\t" << "Help" << endl;
    cout << "Q" << "\t\t" << "Quit" << endl;
}

void InitCombNumb(void)
{
    char cmd = 0;
    uint32_t numb1, numb2;
    int countArg;
    setlocale(LC_ALL, "RUS");

    while (1) {
        countArg = GetArg(cmd, numb1, numb2);

        if (countArg > 0) {
            try {
                switch (cmd) {
                case 'U':
                    if (countArg == 3)
                        cout << U(numb1, numb2) << endl;
                    else
                        throw (string)"Неверное количество аргументов";
                    break;
                case 'A':
                    if (countArg == 3)
                        cout << A(numb1, numb2) << endl;
                    else
                        throw (string)"Неверное количество аргументов";
                    break;
                case 'P':
                    if (countArg == 2)
                        cout << P(numb1) << endl;
                    else
                        throw (string)"Неверное количество аргументов";
                    break;
                case 'C':
                    if (countArg == 3)
                        cout << C(numb1, numb2) << endl;
                    else
                        throw (string)"Неверное количество аргументов";
                    break;
                case 'S':
                    if (countArg == 3)
                        cout << S(numb1, numb2) << endl;
                    else
                        throw (string)"Неверное количество аргументов";
                    break;
                case 'B':
                    if (countArg == 2)
                        cout << B(numb1) << endl;
                    else
                        throw (string)"Неверное количество аргументов";
                    break;
                case 'H':
                    if (countArg == 1)
                        Help();
                    else
                        throw (string)"Неверное количество аргументов";
                    break;
                case 'Q':
                    if (countArg == 1)
                        return;
                    else
                        throw (string)"Неверное количество аргументов";
                    break;
                default:
                    throw (string)"Несуществующая команда";
                    break;
                }
            }
            catch (string const& str) {
                cout << ERROR_STR << str << endl;
            }
        }
    }
}

int main(void)
{
    InitCombNumb();

    return 0;
}
