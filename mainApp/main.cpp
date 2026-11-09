#include <iostream>
#include "Set.h"

Set SieveOfEratosthenes(int n) {
    Set primes(n);

    for (int i = 2; i <= n; ++i) {
        primes.insert(i);
    }

    for (int p = 2; p * p <= n; ++p) {
        if (primes.is_member(p)) {
            for (int i = p * p; i <= n; i += p) {
                primes.erase(i);
            }
        }
    }
    return primes;
}

int main() {
    std::setlocale(LC_ALL, "Russian");
    int n;
    std::cout << "Введите верхнюю границу для поиска простых чисел: ";
    if (std::cin >> n && n >= 2) {
        Set result = SieveOfEratosthenes(n);

        std::cout << "Простые числа до " << n << " в формате множества:\n";
        std::cout << result << "\n";

        std::cout << "\nВ формате битового поля:\n";
        std::cout << static_cast<Bitfield>(result) << "\n";
    }
    else {
        std::cout << "Ошибка ввода. Число должно быть >= 2.\n";
    }
    return 0;
}
