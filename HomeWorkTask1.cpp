#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <vector>
// Выполнил студент Гилязов Тимур, группа 5130203/40002
using namespace std;

const double PI = acos(-1);

// Структура для представления точки на плоскости
struct Point {
    double x;
    double y;
};

// Класс Ellipse (эллипс)
class Ellipse {
private:
    double h, k;       // координаты центра C(h, k)
    double a, b;       // полуоси: a – большая, b – меньшая (всегда a > b)
    bool majorAxisX;   // true, если большая ось вдоль оси X, false – вдоль оси Y

    // Вспомогательный метод для обеспечения a > b.
    void enforceAxes() {
        if (a < b) {
            swap(a, b);
            // Если произошёл обмен, можно также изменить ориентацию:
            majorAxisX = !majorAxisX;
        }
    }
public:
    // Конструктор по умолчанию: центр (0,0), a = 5, b = 3, большая ось вдоль X.
    Ellipse() : h(0), k(0), a(5), b(3), majorAxisX(true) {
        enforceAxes();
    }

    // Параметризованный конструктор.
    Ellipse(double h, double k, double a, double b, bool majorAxisX = true)
        : h(h), k(k), a(a), b(b), majorAxisX(majorAxisX) {
        enforceAxes();
    }

    // Конструктор копирования.
    Ellipse(const Ellipse& other)
        : h(other.h), k(other.k), a(other.a), b(other.b), majorAxisX(other.majorAxisX) {
    }

    // Сеттеры и геттеры.
    void setCenter(double newH, double newK) { h = newH; k = newK; }
    void getCenter(double& outH, double& outK) const { outH = h; outK = k; }

    void setAxes(double newA, double newB) { a = newA; b = newB; enforceAxes(); }
    void getAxes(double& outA, double& outB) const { outA = a; outB = b; }

    void setOrientation(bool isMajorAxisX) { majorAxisX = isMajorAxisX; }
    bool getOrientation() const { return majorAxisX; }

    // Вычисление гиперпараметра эллипса: c = sqrt(a^2 - b^2)
    double getHyperparameter() const {
        return sqrt(a * a - b * b);
    }

    // Получение координат вершин эллипса.
    // Если большая ось вдоль X: (h - a, k) и (h + a, k);
    // если вдоль Y: (h, k - a) и (h, k + a).
    vector<Point> getVertices() const {
        vector<Point> vertices(2);
        if (majorAxisX) {
            vertices[0] = { h - a, k };
            vertices[1] = { h + a, k };
        }
        else {
            vertices[0] = { h, k - a };
            vertices[1] = { h, k + a };
        }
        return vertices;
    }

    // Получение координат фокусов эллипса.
    // Если большая ось вдоль X: (h - c, k) и (h + c, k);
    // если вдоль Y: (h, k - c) и (h, k + c).
    vector<Point> getFoci() const {
        double c = getHyperparameter();
        vector<Point> foci(2);
        if (majorAxisX) {
            foci[0] = { h - c, k };
            foci[1] = { h + c, k };
        }
        else {
            foci[0] = { h, k - c };
            foci[1] = { h, k + c };
        }
        return foci;
    }

    // Длина фокальной хорды (латус ректум): L = 2b^2 / a.
    double getFocalChordLength() const {
        return 2 * (b * b) / a;
    }

    // Эксцентриситет эллипса: e = c / a.
    double getEccentricity() const {
        return getHyperparameter() / a;
    }

    // Печать общего уравнения эллипса и его характерных точек.
    void printEquationAndCharacteristics() const {
        cout << "Ellipse Equation: ";
        if (majorAxisX) {
            cout << "((x - " << h << ")^2)/(" << a * a << ") + ((y - " << k << ")^2)/(" << b * b << ") = 1";
        }
        else {
            cout << "((x - " << h << ")^2)/(" << b * b << ") + ((y - " << k << ")^2)/(" << a * a << ") = 1";
        }
        cout << "\nCenter: (" << h << ", " << k << ")\n";

        vector<Point> vertices = getVertices();
        cout << "Vertices: (" << vertices[0].x << ", " << vertices[0].y << ") and ("
            << vertices[1].x << ", " << vertices[1].y << ")\n";

        vector<Point> foci = getFoci();
        cout << "Foci: (" << foci[0].x << ", " << foci[0].y << ") and ("
            << foci[1].x << ", " << foci[1].y << ")\n";
    }

    // Функция для проверки положения точки (x, y) относительно эллипса.
    // Возвращает: -1 – точка внутри, 0 – на эллипсе, 1 – вне эллипса.
    int pointPosition(double x, double y) const {
        double value;
        if (majorAxisX)
            value = ((x - h) * (x - h)) / (a * a) + ((y - k) * (y - k)) / (b * b);
        else
            value = ((x - h) * (x - h)) / (b * b) + ((y - k) * (y - k)) / (a * a);

        if (fabs(value - 1.0) < 1e-6)
            return 0; // на эллипсе
        else if (value < 1.0)
            return -1; // внутри
        else
            return 1; // снаружи
    }

    // Приблизительный периметр эллипса (формула Рамануяна):
    // P ≈ π [ 3(a+b) - sqrt((3a + b) * (a + 3b)) ]
    double approximatePerimeter() const {
        return PI * (3 * (a + b) - sqrt((3 * a + b) * (a + 3 * b)));
    }

    // Площадь эллипса: S = π * a * b.
    double area() const {
        return PI * a * b;
    }

    // Для заданного значения x (или y) вычислить соответствующие два значения y (или x)
    // Решение уравнения эллипса. Если решений нет – возвращается пустой вектор.
    vector<double> solveForY(double x) const {
        vector<double> results;
        double diff;
        if (majorAxisX) {
            diff = 1 - ((x - h) * (x - h)) / (a * a);
            if (diff < 0) return results;
            double root = b * sqrt(diff);
            results.push_back(k + root);
            results.push_back(k - root);
        }
        else {
            diff = 1 - ((x - h) * (x - h)) / (b * b);
            if (diff < 0) return results;
            double root = a * sqrt(diff);
            results.push_back(k + root);
            results.push_back(k - root);
        }
        return results;
    }

    vector<double> solveForX(double y) const {
        vector<double> results;
        double diff;
        if (majorAxisX) {
            diff = 1 - ((y - k) * (y - k)) / (b * b);
            if (diff < 0) return results;
            double root = a * sqrt(diff);
            results.push_back(h + root);
            results.push_back(h - root);
        }
        else {
            diff = 1 - ((y - k) * (y - k)) / (a * a);
            if (diff < 0) return results;
            double root = b * sqrt(diff);
            results.push_back(h + root);
            results.push_back(h - root);
        }
        return results;
    }
};

// Класс Quaternion (кватернион)
class Quaternion {
private:
    double a, b, c, d; // a – действительная часть, b, c, d – мнимые компоненты
public:
    // Конструктор по умолчанию: 1 + 0i + 0j + 0k.
    Quaternion() : a(1), b(0), c(0), d(0) {}

    // Параметризованный конструктор.
    Quaternion(double a, double b, double c, double d) : a(a), b(b), c(c), d(d) {}

    // Конструктор копирования.
    Quaternion(const Quaternion& q) : a(q.a), b(q.b), c(q.c), d(q.d) {}

    // Сеттеры
    void setA(double val) { a = val; }
    void setB(double val) { b = val; }
    void setC(double val) { c = val; }
    void setD(double val) { d = val; }
    void setAll(double a, double b, double c, double d) { this->a = a; this->b = b; this->c = c; this->d = d; }

    // Геттеры
    double getA() const { return a; }
    double getB() const { return b; }
    double getC() const { return c; }
    double getD() const { return d; }

    // Вывод кватерниона в стандартном формате.
    void print() const {
        cout << a;
        if (b >= 0) cout << " + " << b << "i"; else cout << " - " << fabs(b) << "i";
        if (c >= 0) cout << " + " << c << "j"; else cout << " - " << fabs(c) << "j";
        if (d >= 0) cout << " + " << d << "k"; else cout << " - " << fabs(d) << "k";
    }

    // Норма кватерниона: ||q|| = sqrt(a^2 + b^2 + c^2 + d^2).
    double norm() const {
        return sqrt(a * a + b * b + c * c + d * d);
    }

    // Сопряжённый кватернион: (a, -b, -c, -d).
    Quaternion conjugate() const {
        return Quaternion(a, -b, -c, -d);
    }

    // Нормализация кватерниона: делим на норму.
    Quaternion normalize() const {
        double n = norm();
        if (n == 0)
            throw runtime_error("Cannot normalize a zero quaternion.");
        return Quaternion(a / n, b / n, c / n, d / n);
    }

    // Инверсия кватерниона: inverse(q) = conjugate(q) / (norm(q)^2).
    Quaternion inverse() const {
        double n2 = a * a + b * b + c * c + d * d;
        if (n2 == 0)
            throw runtime_error("Cannot invert a zero quaternion.");
        Quaternion conj = conjugate();
        return Quaternion(conj.a / n2, conj.b / n2, conj.c / n2, conj.d / n2);
    }
};

// Перегрузка операторов для арифметики с кватернионами.

// Сложение
Quaternion operator+(const Quaternion& q1, const Quaternion& q2) {
    return Quaternion(q1.getA() + q2.getA(), q1.getB() + q2.getB(),
        q1.getC() + q2.getC(), q1.getD() + q2.getD());
}

// Вычитание
Quaternion operator-(const Quaternion& q1, const Quaternion& q2) {
    return Quaternion(q1.getA() - q2.getA(), q1.getB() - q2.getB(),
        q1.getC() - q2.getC(), q1.getD() - q2.getD());
}

// Умножение (гамильтоново произведение)
Quaternion operator*(const Quaternion& q1, const Quaternion& q2) {
    double a = q1.getA() * q2.getA() - q1.getB() * q2.getB() - q1.getC() * q2.getC() - q1.getD() * q2.getD();
    double b = q1.getA() * q2.getB() + q1.getB() * q2.getA() + q1.getC() * q2.getD() - q1.getD() * q2.getC();
    double c = q1.getA() * q2.getC() - q1.getB() * q2.getD() + q1.getC() * q2.getA() + q1.getD() * q2.getB();
    double d = q1.getA() * q2.getD() + q1.getB() * q2.getC() - q1.getC() * q2.getB() + q1.getD() * q2.getA();
    return Quaternion(a, b, c, d);
}

// Деление: q1 / q2 = q1 * inverse(q2)
Quaternion operator/(const Quaternion& q1, const Quaternion& q2) {
    return q1 * q2.inverse();
}

// Скалярное (dot) произведение двух кватернионов
double dot(const Quaternion& q1, const Quaternion& q2) {
    return q1.getA() * q2.getA() + q1.getB() * q2.getB() + q1.getC() * q2.getC() + q1.getD() * q2.getD();
}

// Евклидово расстояние между двумя кватернионами
double euclideanDistance(const Quaternion& q1, const Quaternion& q2) {
    double da = q1.getA() - q2.getA();
    double db = q1.getB() - q2.getB();
    double dc = q1.getC() - q2.getC();
    double dd = q1.getD() - q2.getD();
    return sqrt(da * da + db * db + dc * dc + dd * dd);
}

// Норма Чебышева (max разность компонент) между двумя кватернионами
double chebyshevNorm(const Quaternion& q1, const Quaternion& q2) {
    double da = fabs(q1.getA() - q2.getA());
    double db = fabs(q1.getB() - q2.getB());
    double dc = fabs(q1.getC() - q2.getC());
    double dd = fabs(q1.getD() - q2.getD());
    return max({ da, db, dc, dd });
}

int main() {
    // Демонстрация работы класса Ellipse
    cout << "=== Ellipse Demonstration ===\n";
    Ellipse e1(1, 2, 5, 3, true); // центр (1,2), a = 5, b = 3, большая ось вдоль X
    e1.printEquationAndCharacteristics();
    cout << fixed << setprecision(3);
    cout << "Hyperparameter c: " << e1.getHyperparameter() << "\n";
    cout << "Focal chord length: " << e1.getFocalChordLength() << "\n";
    cout << "Eccentricity: " << e1.getEccentricity() << "\n";
    cout << "Approximate Perimeter: " << e1.approximatePerimeter() << "\n";
    cout << "Area: " << e1.area() << "\n";

    double testX = 3;
    vector<double> ySolutions = e1.solveForY(testX);
    if (!ySolutions.empty()) {
        cout << "For x = " << testX << ", y = " << ySolutions[0] << " or " << ySolutions[1] << "\n";
    }
    else {
        cout << "No real y for x = " << testX << "\n";
    }

    int pos = e1.pointPosition(3, 2);
    cout << "Point (3,2) is ";
    if (pos == -1)
        cout << "inside the ellipse.\n";
    else if (pos == 0)
        cout << "on the ellipse.\n";
    else
        cout << "outside the ellipse.\n";

    // Демонстрация работы класса Quaternion
    cout << "\n=== Quaternion Demonstration ===\n";
    Quaternion q1; // по умолчанию: 1 + 0i + 0j + 0k
    Quaternion q2(2, 3, 4, 5);
    cout << "q1 = "; q1.print(); cout << "\n";
    cout << "q2 = "; q2.print(); cout << "\n";

    Quaternion qAdd = q1 + q2;
    cout << "q1 + q2 = "; qAdd.print(); cout << "\n";

    Quaternion qSub = q1 - q2;
    cout << "q1 - q2 = "; qSub.print(); cout << "\n";

    Quaternion qMul = q1 * q2;
    cout << "q1 * q2 = "; qMul.print(); cout << "\n";

    Quaternion qDiv = q2 / q1; // поскольку q1 – единичный кватернион, результат равен q2.
    cout << "q2 / q1 = "; qDiv.print(); cout << "\n";

    cout << "Norm of q2: " << q2.norm() << "\n";
    cout << "Conjugate of q2: ";
    Quaternion qConj = q2.conjugate();
    qConj.print();
    cout << "\n";

    cout << "Normalized q2: ";
    Quaternion qNorm = q2.normalize();
    qNorm.print();
    cout << "\n";

    cout << "Inverse of q2: ";
    Quaternion qInv = q2.inverse();
    qInv.print();
    cout << "\n";

    cout << "Dot product q1 . q2: " << dot(q1, q2) << "\n";
    cout << "Euclidean distance between q1 and q2: " << euclideanDistance(q1, q2) << "\n";
    cout << "Chebyshev norm between q1 and q2: " << chebyshevNorm(q1, q2) << "\n";

    return 0;
}
