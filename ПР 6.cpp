#include <iostream>   // подключаем библиотеку для ввода-вывода (cin, cout)
using namespace std;  // чтобы не писать std:: перед cin и cout

int main() {
    int n;
    cin >> n;         // считываем размер квадрата N (от 1 до 100)

    for (int i = 0; i < n; i++) {           // перебираем строки матрицы: i = 0..n-1
        for (int j = 0; j < n; j++) {       // перебираем столбцы матрицы: j = 0..n-1
            // сравниваем сумму индексов с n-1 — так находим положение
            // относительно побочной диагонали (она задана условием i + j = n - 1)
            if (i + j < n - 1)
                cout << 0;                  // выше побочной диагонали -> ноль
            else if (i + j == n - 1)
                cout << 1;                  // на самой диагонали -> единица
            else
                cout << 2;                  // ниже диагонали -> два

            if (j < n - 1)
                cout << ' ';                // пробел между цифрами, после последней не ставим
        }
        cout << '\n';                      
    }
    return 0;                               
}


#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i + j < n - 1)
                cout << 0;
            else if (i + j == n - 1)
                cout << 1;
            else
                cout << 2;

            if (j < n - 1)
                cout << ' '; 
        }
        cout << '\n';
    }
    return 0;
}


#include <iostream>   // библиотека для ввода-вывода (cin, cout)
using namespace std;  // чтобы не писать std:: перед cin и cout

int main() {
    int n, m, w;
    cin >> n >> m >> w;   // n — число строк, m — число столбцов, w — число грибов

    // поле: true — в клетке стоит гриб, false — клетка пустая
    // размеры 32x32 взяты с запасом, по условию n и m не превышают 32
    bool mush[32][32] = {false};

    for (int i = 0; i < w; i++) {
        int r, c;
        cin >> r >> c;                 // координата гриба: строка и столбец (с единицы)
        mush[r - 1][c - 1] = true;     // сдвигаем на -1, так как индексы массива идут с нуля
    }

    // для каждой клетки считаем, сколько грибов находится в соседних клетках
    int cnt[32][32] = {0};
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            int k = 0;                             // счётчик грибов-соседей
            for (int di = -1; di <= 1; di++)       // смещение по строке: -1, 0, 1
                for (int dj = -1; dj <= 1; dj++) { // смещение по столбцу: -1, 0, 1
                    if (di == 0 && dj == 0) continue;   // саму клетку не считаем, только 8 соседей
                    int ni = i + di, nj = j + dj;       // координаты соседней клетки
                    // сосед учитывается, если он не выходит за границу поля
                    // и в нём стоит гриб
                    if (ni >= 0 && ni < n && nj >= 0 && nj < m && mush[ni][nj])
                        k++;
                }
            cnt[i][j] = k;     // запоминаем число грибов вокруг клетки (i, j)
        }

    // вывод: как в «сапёре» — гриб или число соседей, без пробелов
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            if (mush[i][j])
                cout << '*';           // в клетке гриб — печатаем звёздочку
            else
                cout << cnt[i][j];     // иначе — количество грибов по соседству
        cout << '\n';                  // переход на следующую строку поля
    }
    return 0;                          // программа завершилась успешно
}



#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
    int n, m, w;
    cin >> n >> m >> w;

    int r[1000], c[1000];
    for (int i = 0; i < w; i++)
        cin >> r[i] >> c[i];

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            bool isMush = false;
            int cnt = 0;
            for (int k = 0; k < w; k++) {
                if (r[k] == i && c[k] == j)
                    isMush = true;
                else if (abs(r[k] - i) <= 1 && abs(c[k] - j) <= 1)
                    cnt++;
            }
            if (isMush) cout << '*';
            else        cout << cnt;
        }
        cout << '\n';
    }
    return 0;
}



#include <iostream>   // библиотека для ввода-вывода (cin, cout)
#include <string>     // библиотека для работы со строками (string, to_string)
using namespace std;  // чтобы не писать std:: перед cin и cout

int main() {
    int x, n;
    cin >> x >> n;    // x — первый член последовательности, n — номер нужной строки

    string s = to_string(x);   // первая строка последовательности — само число x

    // нужно выполнить преобразование n-1 раз:
    // строка номер 1 уже есть (это s), получаем строки 2, 3, ..., n
    for (int step = 1; step < n; step++) {
        string next = "";     // здесь соберём следующую строку последовательности
        int i = 0;

        // идём по строке слева направо, обрабатывая за раз одну группу
        // одинаковых подряд идущих цифр
        while (i < (int)s.size()) {
            int j = i;
            // двигаем j, пока цифры совпадают с s[i] — так находим конец группы
            while (j < (int)s.size() && s[j] == s[i]) j++;

            next += to_string(j - i);   // приписываем количество цифр в группе
            next += s[i];               // затем саму цифру

            i = j;                      // перескакиваем на начало следующей группы
        }
        s = next;                       // новая строка становится текущей
    }

    cout << s << '\n';    // выводим n-ю строку последовательности
    return 0;             // программа завершилась успешно
}


#include <iostream>
#include <string>
using namespace std;

string lookAndSay(const string& s) {
    string next = "";
    int count = 1;
    for (int k = 1; k <= (int)s.size(); k++) {
        if (k < (int)s.size() && s[k] == s[k - 1]) {
            count++;
        } else {
            next += to_string(count);
            next += s[k - 1];
            count = 1;
        }
    }
    return next;
}

int main() {
    int x, n;
    cin >> x >> n;

    string s = to_string(x);
    for (int step = 1; step < n; step++)
        s = lookAndSay(s);

    cout << s << '\n';
    return 0;
}

