#include <iostream>
#include <string>
#include <algorithm>
#include <limits> // Для обработки ввода
using namespace std;

// Функция для удаления ведущих нулей
string removeLeadingZeros(const string& num) {
    size_t firstNonZero = num.find_first_not_of('0');
    if (firstNonZero == string::npos) return "0"; // все нули
    return num.substr(firstNonZero);
}

// Функция для сложения двух больших чисел
string bigAdd(const string& num1, const string& num2) {
    string result;
    int carry = 0;

    int maxLength = max(num1.length(), num2.length());
    string n1 = string(maxLength - num1.length(), '0') + num1;
    string n2 = string(maxLength - num2.length(), '0') + num2;

    for (int i = maxLength - 1; i >= 0; i--) {
        int sum = (n1[i] - '0') + (n2[i] - '0') + carry;
        carry = sum / 10;
        result += (sum % 10) + '0';
    }

    if (carry > 0) {
        result += carry + '0';
    }

    reverse(result.begin(), result.end());

    return removeLeadingZeros(result);
}

// Функция для умножения "большого числа" на малое целое
string bigMultiply(const string& num, int multiplier) {
    string result;

    int carry = 0;

    for (int i = num.length() - 1; i >= 0; i--) {
        int prod = (num[i] - '0') * multiplier + carry;
        carry = prod / 10;
        result += (prod % 10) + '0';
    }

    while (carry > 0) {
        result += (carry % 10) + '0';
        carry /= 10;
    }

    reverse(result.begin(), result.end());
    return removeLeadingZeros(result);
}

// Функция для возведения в степень
string bigPower(int base, int exp) {
    string result = "1";

    for (int i = 0; i < exp; i++) {
        result = bigMultiply(result, base);
    }

    return removeLeadingZeros(result);
}

// Основная функция
int main() {
    setlocale(LC_ALL, "RU");
    string s;
    int n;

    while (true) {
        cout << "Введите n (n >= 10): ";
        cin >> s;

        // Проверка на корректный ввод
        try {
            n = stoi(s); // Попробуем конвертировать строку в целое число

            if (n < 10) {
                cout << "Ошибка: n должно быть больше или равно 10." << endl;
            }
            else {
                break; // Число корректное, выходим из цикла
            }
        }
        catch (invalid_argument& e) { // Обработка некорректного ввода
            cout << "Ошибка: введите только целое неотрицательное число." << endl;
        }
        catch (out_of_range& e) { // Обработка выхода за пределы целого
            cout << "Ошибка: число вне допустимого диапазона." << endl;
        }

        // Очищаем ввод в случае некорректного ввода
        cin.clear(); // Сбрасываем состояние потока
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Игнорируем оставшиеся символы в потоке
    }

    string sum = "0"; // строка для хранения суммы

    // Вычисляем сумму 1^n + 2^n + ... + n^n
    for (int i = 1; i <= n; i++) {
        string power = bigPower(i, n);
        cout << i << "^" << n << " = " << power << endl; // Вывод промежуточного результата
        sum = bigAdd(sum, power);
    }

    // Вывод результата
    cout << "Сумма 1^" << n << " + 2^" << n << " + ... + " << n << "^" << n << " = " << removeLeadingZeros(sum) << endl;

    return 0;
}