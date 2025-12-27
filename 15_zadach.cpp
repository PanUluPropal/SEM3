#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <cstdlib>
#include <ctime>
using namespace std;

// -------------------------------------------------------------
// Глобальные данные траектории ракеты
// -------------------------------------------------------------
vector<double> times;
vector<double> heights;
vector<double> velocities;

// -------------------------------------------------------------
// ЗАДАЧА 1: Моделирование высоты ракеты во времени
// -------------------------------------------------------------
void Zadacha1() {
    cout << "\n--- Задача 1: Таблица высоты ракеты ---\n";

    const double v0 = 50.0;
    const double g = 9.8;
    const double dt = 1.0;

    times.clear();
    heights.clear();

    for (double t = 0; t <= 1000; t += dt) {
        double h = v0 * t - 0.5 * g * t * t;
        if (h < 0) break;
        times.push_back(t);
        heights.push_back(h);
    }

    cout << setw(10) << "t (с)" << setw(12) << "h (м)" << endl;
    for (size_t i = 0; i < times.size(); i++)
        cout << setw(10) << times[i] << setw(12) << heights[i] << endl;
}

// -------------------------------------------------------------
void Zadacha2() {
    cout << "\n--- Задача 2: Максимальная высота ---\n";

    if (heights.empty()) {
        cout << "Нет данных, сначала выполните задачу 1.\n";
        return;
    }

    size_t idx = 0;
    for (size_t i = 1; i < heights.size(); i++)
        if (heights[i] > heights[idx]) idx = i;

    cout << "Максимальная высота: " << heights[idx] << " м\n";
    cout << "Достигнута в момент t = " << times[idx] << " с\n";
}

// -------------------------------------------------------------
void Zadacha3() {
    cout << "\n--- Задача 3: Вектор скоростей ---\n";

    if (times.empty()) {
        cout << "Нет данных.\n";
        return;
    }

    velocities.clear();
    const double g = 9.8;
    const double v0 = 50.0;

    for (double t : times)
        velocities.push_back(v0 - g * t);

    cout << setw(10) << "t" << setw(12) << "v" << endl;
    for (size_t i = 0; i < velocities.size(); i++)
        cout << setw(10) << times[i] << setw(12) << velocities[i] << endl;
}

// -------------------------------------------------------------
void Zadacha4() {
    cout << "\n--- Задача 4: Средняя скорость ---\n";

    if (velocities.empty()) {
        cout << "Сначала выполните задачу 3.\n";
        return;
    }

    double sum = accumulate(velocities.begin(), velocities.end(), 0.0);
    cout << "Средняя скорость: " << sum / velocities.size() << " м/с\n";
}

// -------------------------------------------------------------
struct Point { double x, y, z; };

void Zadacha5() {
    cout << "\n--- Задача 5: 3D траектория ---\n";

    vector<Point> traj;
    traj.reserve(20);

    double x = 0, y = 0, z = 0;
    double vx = 30, vy = 20, vz = 40;

    cout << setw(8) << "t" << setw(10) << "x"
        << setw(10) << "y" << setw(10) << "z" << endl;

    for (double t = 0; t <= 10; t += 1) {
        x += vx; y += vy; z += vz;
        cout << setw(8) << t << setw(10) << x
            << setw(10) << y << setw(10) << z << endl;
    }
}

// -------------------------------------------------------------
void Zadacha6() {
    cout << "\n--- Задача 6: Удаление высот < 10 м ---\n";

    if (heights.empty()) {
        cout << "Нет данных.\n";
        return;
    }

    auto it = remove_if(heights.begin(), heights.end(),
        [](double h) { return h < 10; });
    heights.erase(it, heights.end());

    cout << "Оставшиеся высоты: ";
    for (double h : heights) cout << h << " ";
    cout << endl;
}

// -------------------------------------------------------------
void Zadacha7() {
    cout << "\n--- Задача 7: Момент падения ---\n";

    if (heights.empty()) {
        cout << "Нет данных.\n";
        return;
    }

    auto it = find_if(heights.begin(), heights.end(),
        [](double h) { return h <= 0; });

    if (it == heights.end()) cout << "Падения нет.\n";
    else {
        size_t idx = distance(heights.begin(), it);
        cout << "Падение в момент t = " << times[idx] << " с\n";
    }
}

// -------------------------------------------------------------
void Zadacha8() {
    cout << "\n--- Задача 8: Сравнение двух ракет ---\n";

    vector<double> h1, h2;
    double v1 = 50, v2 = 60;

    for (double t = 0;; t += 1) {
        double h = v1 * t - 4.9 * t * t;
        if (h < 0) break;
        h1.push_back(h);
    }
    for (double t = 0;; t += 1) {
        double h = v2 * t - 4.9 * t * t;
        if (h < 0) break;
        h2.push_back(h);
    }

    double max1 = *max_element(h1.begin(), h1.end());
    double max2 = *max_element(h2.begin(), h2.end());

    cout << "Ракета 1: " << max1 << " м\n";
    cout << "Ракета 2: " << max2 << " м\n";
}

// -------------------------------------------------------------
void Zadacha9() {
    cout << "\n--- Задача 9: Сглаживание ---\n";

    if (heights.size() < 3) {
        cout << "Недостаточно точек.\n";
        return;
    }

    vector<double> sm(heights.size());
    sm[0] = heights[0];
    sm.back() = heights.back();

    for (size_t i = 1; i + 1 < heights.size(); i++)
        sm[i] = (heights[i - 1] + heights[i] + heights[i + 1]) / 3.0;

    cout << setw(10) << "h" << setw(12) << "smooth" << endl;
    for (size_t i = 0; i < sm.size(); i++)
        cout << setw(10) << heights[i] << setw(12) << sm[i] << endl;
}

// -------------------------------------------------------------
class Rocket {
public:
    double x, y, z, vx, vy, vz;
    Rocket(double X, double Y, double Z, double VX, double VY, double VZ)
        :x(X), y(Y), z(Z), vx(VX), vy(VY), vz(VZ) {
    }
    void update() { x += vx; y += vy; z += vz; }
};

void Zadacha10() {
    cout << "\n--- Задача 10: Отряд ракет ---\n";

    vector<Rocket> squad{
        {0,0,0,30,0,50},
        {0,0,0,40,5,45},
        {0,0,0,25,-2,60},
        {0,0,0,35,8,55},
        {0,0,0,45,-6,40}
    };

    for (int t = 0; t <= 10; t++)
        for (auto& r : squad) r.update();

    for (int i = 0; i < squad.size(); i++)
        cout << "Ракета " << i + 1 << " → x=" << squad[i].x
        << " y=" << squad[i].y << " z=" << squad[i].z << endl;
}

// -------------------------------------------------------------
// ДОПОЛНИТЕЛЬНЫЕ ЗАДАЧИ STL (11–15)
// -------------------------------------------------------------
void Zadacha11() { Zadacha2(); }

void Zadacha12() {
    cout << "\n--- Задача 12: Подсчёт нулей ---\n";
    vector<double>a{ 0,1,0,2.3,0 };
    cout << "Нулей: " << count(a.begin(), a.end(), 0.0) << endl;
}

void Zadacha13() {
    cout << "\n--- Задача 13: Очистка шума ---\n";
    vector<double>a{ 150,-200,180,210,200,-150,170 };
    auto it = remove_if(a.begin(), a.end(),
        [](double x) {return x < -100 || x>200; });
    a.erase(it, a.end());
    for (double x : a)cout << x << " ";
    cout << endl;
}

void Zadacha14() {
    cout << "\n--- Задача 14: Путь ракеты ---\n";
    vector<double>y{ 0,5,20,45,70 };
    vector<double>d(y.size());
    adjacent_difference(y.begin(), y.end(), d.begin());
    d[0] = 0;
    double sum = accumulate(d.begin(), d.end(), 0.0,
        [](double s, double v) {return s + fabs(v); });
    cout << "Путь: " << sum << " м\n";
}

void Zadacha15() {
    cout << "\n--- Задача 15: Сортировка и удаление дублей ---\n";
    vector<double>x{ 5,2,5,7,2,9 };
    sort(x.begin(), x.end());
    x.erase(unique(x.begin(), x.end()), x.end());
    for (double t : x)cout << t << " ";
    cout << endl;
}

// -------------------------------------------------------------
// ГЛАВНОЕ МЕНЮ
// -------------------------------------------------------------
int main() {
    setlocale(LC_ALL, "Russian");

    int c;
    do {
        cout << "\n=========== МЕНЮ ЗАДАЧ ПРО РАКЕТУ ===========\n";
        cout << "1  - Высота ракеты\n";
        cout << "2  - Максимальная высота\n";
        cout << "3  - Скорости\n";
        cout << "4  - Средняя скорость\n";
        cout << "5  - 3D координаты\n";
        cout << "6  - Удаление малых высот\n";
        cout << "7  - Момент падения\n";
        cout << "8  - Сравнение ракет\n";
        cout << "9  - Сглаживание\n";
        cout << "10 - Отряд ракет\n";
        cout << "------- Дополнительные задачи STL ------\n";
        cout << "11 - Max высота\n";
        cout << "12 - Подсчёт нулей\n";
        cout << "13 - Очистка выбросов\n";
        cout << "14 - Путь\n";
        cout << "15 - Сортировка и уникальность\n";
        cout << "0  - Выход\n";
        cout << "Ваш выбор: ";
        cin >> c;

        switch (c) {
        case 1: Zadacha1(); break;
        case 2: Zadacha2(); break;
        case 3: Zadacha3(); break;
        case 4: Zadacha4(); break;
        case 5: Zadacha5(); break;
        case 6: Zadacha6(); break;
        case 7: Zadacha7(); break;
        case 8: Zadacha8(); break;
        case 9: Zadacha9(); break;
        case 10: Zadacha10(); break;
        case 11: Zadacha11(); break;
        case 12: Zadacha12(); break;
        case 13: Zadacha13(); break;
        case 14: Zadacha14(); break;
        case 15: Zadacha15(); break;
        case 0: cout << "Выход...\n"; break;
        default: cout << "Неверный пункт!\n";
        }

    } while (c != 0);

    return 0;
}
