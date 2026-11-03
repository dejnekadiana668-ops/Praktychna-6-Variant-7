#include <iostream>
using namespace std;

const int MAX = 1000;

// Структура для підрахунку операцій
struct Statystyka {
    long long porivnyannya = 0;
    long long obminy = 0;
};

// Виведення масиву
void pokazaty(const int a[], int n) {
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
}

// Обмін двох елементів
void obmin(int& a, int& b, Statystyka& s) {
    int temp = a;
    a = b;
    b = temp;
    s.obminy++;
}

// Завдання 1. Перевірка максимальної купи
bool perevirkaKupy(const int a[], int n) {
    for (int i = 0; i < n; i++) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (l < n && a[i] < a[l])
            return false;

        if (r < n && a[i] < a[r])
            return false;
    }

    return true;
}

// Завдання 2. Відновлення купи
void vidnovyty(int a[], int n, int i, Statystyka& s) {
    while (true) {
        int maxIndex = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (l < n) {
            s.porivnyannya++;

            if (a[l] > a[maxIndex])
                maxIndex = l;
        }

        if (r < n) {
            s.porivnyannya++;

            if (a[r] > a[maxIndex])
                maxIndex = r;
        }

        if (maxIndex == i)
            break;

        obmin(a[i], a[maxIndex], s);
        i = maxIndex;
    }
}

// Завдання 3. Побудова максимальної купи
void pobuduvaty(int a[], int n, Statystyka& s,
    bool trasa = false) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        vidnovyty(a, n, i, s);

        if (trasa) {
            cout << "Вузол " << i << ": ";
            pokazaty(a, n);
        }
    }
}

// Завдання 4. Сортування купою
void heapSort(int a[], int n,
    Statystyka& bud, Statystyka& sort,
    bool trasa = false) {
    pobuduvaty(a, n, bud, trasa);

    if (trasa) {
        cout << "Купу побудовано: "
            << (perevirkaKupy(a, n) ? "так" : "ні")
            << endl;
    }

    for (int i = n - 1; i > 0; i--) {
        obmin(a[0], a[i], sort);
        vidnovyty(a, i, 0, sort);

        if (trasa) {
            cout << "Вилучення " << n - i
                << ", розмір купи " << i << ": ";
            pokazaty(a, n);

            cout << "Купа правильна: "
                << (perevirkaKupy(a, i) ? "так" : "ні")
                << endl;
        }
    }
}

// Завдання 6. Перевірка збереження чисел
bool sklad(const int a[], const int b[], int n) {
    for (int i = 0; i < n; i++) {
        int k1 = 0, k2 = 0;

        for (int j = 0; j < n; j++) {
            if (a[j] == a[i])
                k1++;

            if (b[j] == a[i])
                k2++;
        }

        if (k1 != k2)
            return false;
    }

    for (int i = 0; i < n; i++) {
        int k1 = 0, k2 = 0;

        for (int j = 0; j < n; j++) {
            if (b[j] == b[i])
                k1++;

            if (a[j] == b[i])
                k2++;
        }

        if (k1 != k2)
            return false;
    }

    return true;
}

// Перевірка сортування за зростанням
bool vporiadkovano(const int a[], int n) {
    for (int i = 1; i < n; i++) {
        if (a[i - 1] > a[i])
            return false;
    }

    return true;
}

// Завдання 7. Порівняльний експеримент
void eksperyment(int n, int typ) {
    int a[MAX];

    for (int i = 0; i < n; i++) {
        if (typ == 1)
            a[i] = i + 1;
        else if (typ == 2)
            a[i] = n - i;
        else
            a[i] = (i * 37 + 11) % 101;
    }

    Statystyka bud, sort;
    heapSort(a, n, bud, sort);

    cout << n << " | "
        << bud.porivnyannya << " | "
        << bud.obminy << " | "
        << sort.porivnyannya << " | "
        << sort.obminy << endl;
}

// Завдання 8. Автоматизовані тести
void test(const int a[], int n, int nomer) {
    int b[MAX];

    for (int i = 0; i < n; i++)
        b[i] = a[i];

    Statystyka bud, sort;
    heapSort(b, n, bud, sort);

    bool ok = vporiadkovano(b, n) && sklad(a, b, n);

    cout << "Тест " << nomer << ": "
        << (ok ? "успішно" : "помилка")
        << endl;
}

int main() {
    const int n = 15;

    // Початковий масив варіанта 7
    int a[n] = {
        20, 32, 7, 25, 11, 3, 28, 14,
        1, 22, 9, 30, 5, 17, 12
    };

    int b[n];

    for (int i = 0; i < n; i++)
        b[i] = a[i];

    // ===================================
    // Завдання 1. Перевірка купи
    // ===================================

    cout << "\nЗавдання 1. Перевірка купи\n";

    cout << "Початковий масив: ";
    pokazaty(a, n);

    cout << "Максимальна купа: "
        << (perevirkaKupy(a, n) ? "так" : "ні")
        << endl;

    // ===================================
    // Завдання 2. Відновлення купи
    // Завдання 3. Побудова купи
    // ===================================

    cout << "\nЗавдання 2-3. Побудова купи\n";

    Statystyka bud;
    pobuduvaty(b, n, bud, true);

    cout << "Перевірка купи: "
        << (perevirkaKupy(b, n) ? "успішно" : "помилка")
        << endl;

    // ===================================
    // Завдання 4. Сортування
    // ===================================

    cout << "\nЗавдання 4. Сортування\n";

    Statystyka sort;

    for (int i = n - 1; i > 0; i--) {
        obmin(b[0], b[i], sort);
        vidnovyty(b, i, 0, sort);

        cout << "Вилучення " << n - i
            << ", розмір купи " << i << ": ";
        pokazaty(b, n);

        cout << "Купа правильна: "
            << (perevirkaKupy(b, i) ? "так" : "ні")
            << endl;
    }

    cout << "Відсортований масив: ";
    pokazaty(b, n);

    // ===================================
    // Завдання 5. Статистика
    // ===================================

    cout << "\nЗавдання 5. Статистика\n";

    cout << "Побудова: порівнянь " << bud.porivnyannya
        << ", обмінів " << bud.obminy << endl;

    cout << "Сортування: порівнянь " << sort.porivnyannya
        << ", обмінів " << sort.obminy << endl;

    cout << "Усього порівнянь: "
        << bud.porivnyannya + sort.porivnyannya << endl;

    cout << "Усього обмінів: "
        << bud.obminy + sort.obminy << endl;

    long long pobudova = bud.porivnyannya + bud.obminy;

    long long vsi = pobudova
        + sort.porivnyannya
        + sort.obminy;

    cout << "Частка побудови: ";

    if (vsi > 0)
        cout << 100.0 * pobudova / vsi << "%\n";
    else
        cout << "0%\n";

    // ===================================
    // Завдання 6. Перевірка складу
    // ===================================

    cout << "\nЗавдання 6. Перевірка складу\n";

    cout << (sklad(a, b, n) ? "Усі числа збережено"
        : "Помилка складу")
        << endl;

    // ===================================
    // Завдання 7. Порівняльний експеримент
    // ===================================

    cout << "\nЗавдання 7. Порівняльний експеримент\n";

    cout << "n | Поб.пор | Поб.обм | Сорт.пор | Сорт.обм\n";

    cout << "\nЗростаючий масив:\n";
    eksperyment(100, 1);
    eksperyment(1000, 1);

    cout << "\nСпадний масив:\n";
    eksperyment(100, 2);
    eksperyment(1000, 2);

    cout << "\nЗмішаний масив:\n";
    eksperyment(100, 3);
    eksperyment(1000, 3);

    // ===================================
    // Завдання 8. Автоматизовані тести
    // ===================================

    cout << "\nЗавдання 8. Автоматизовані тести\n";

    int t1[] = { 5 };
    int t2[] = { 2, 1 };
    int t3[] = { 1, 2, 3, 4, 5 };
    int t4[] = { 5, 4, 3, 2, 1 };
    int t5[] = { 3, 3, 3, 3 };
    int t6[] = { 4, 1, 4, 2, 1 };
    int t7[] = { -3, 0, 5, -1, 2 };
    int t8[] = { 10, 7, 8, 9, 1, 5 };
    int t9[] = { 0, -1, 0, -1, 0 };
    int t10[] = { 8, 8, 2, 9, 2, 1 };

    test(a, n, 1);
    test(t1, 1, 2);
    test(t2, 2, 3);
    test(t3, 5, 4);
    test(t4, 5, 5);
    test(t5, 4, 6);
    test(t6, 5, 7);
    test(t7, 5, 8);
    test(t8, 6, 9);
    test(t9, 5, 10);
    test(t10, 6, 11);
    test(a, 0, 12);

    return 0;
}
