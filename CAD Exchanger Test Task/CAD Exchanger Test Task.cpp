#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

// Базовый класс для трехмерных геометрических кривых
class Curve3D {
public:
    virtual double radius() const = 0;
    virtual double evaluateX(double t) const = 0;
    virtual double evaluateY(double t) const = 0;
    virtual double evaluateZ(double t) const = 0;
    virtual double derivativeX(double t) const = 0;
    virtual double derivativeY(double t) const = 0;
    virtual double derivativeZ(double t) const = 0;
};

// Класс для кругов
class Circle : public Curve3D {
private:
    double centerX;
    double centerY;
    double centerZ;
    double r;

public:
    Circle(double x, double y, double z, double radius)
        : centerX(x), centerY(y), centerZ(z), r(radius) {}

    ~Circle() {}

    double radius() const override {
        return r;
    }

    double evaluateX(double t) const override {
        return centerX + r * cos(t);
    }

    double evaluateY(double t) const override {
        return centerY + r * sin(t);
    }

    double evaluateZ(double t) const override {
        return centerZ;
    }

    double derivativeX(double t) const override {
        return -r * sin(t);
    }

    double derivativeY(double t) const override {
        return r * cos(t);
    }

    double derivativeZ(double t) const override {
        return 0.0;
    }
};

// Класс для эллипсов
class Ellipse : public Curve3D {
private:
    double centerX;
    double centerY;
    double centerZ;
    double a;
    double b;

public:
    Ellipse(double x, double y, double z, double semiMajorAxis, double semiMinorAxis)
        : centerX(x), centerY(y), centerZ(z), a(semiMajorAxis), b(semiMinorAxis) {}

    ~Ellipse() {}

    double radius() const override {
        return (a + b) / 2;
    }

    double evaluateX(double t) const override {
        return centerX + a * cos(t);
    }

    double evaluateY(double t) const override {
        return centerY + b * sin(t);
    }

    double evaluateZ(double t) const override {
        return centerZ;
    }

    double derivativeX(double t) const override {
        return -a * sin(t);
    }

    double derivativeY(double t) const override {
        return b * cos(t);
    }

    double derivativeZ(double t) const override {
        return 0.0;
    }
};

// Класс для трехмерных спиралей
class Spiral : public Curve3D {
private:
    double centerX;
    double centerY;
    double centerZ;
    double a;
    double b;

public:
    Spiral(double x, double y, double z, double semiMajorAxis, double semiMinorAxis)
        : centerX(x), centerY(y), centerZ(z), a(semiMajorAxis), b(semiMinorAxis) {}

    ~Spiral() {}

    double radius() const override {
        return (a + b) / 2;
    }

    double evaluateX(double t) const override {
        return centerX + a * cos(t);
    }

    double evaluateY(double t) const override {
        return centerY + b * sin(t);
    }

    double evaluateZ(double t) const override {
        return centerZ + (t / (2 * M_PI)) * (a + b);
    }

    double derivativeX(double t) const override {
        return -a * sin(t);
    }

    double derivativeY(double t) const override {
        return b * cos(t);
    }

    double derivativeZ(double t) const override {
        double r = (a + b) / 2;
        return (a + b) / (2 * M_PI * r);
    }
};

int main() {
    std::vector<Curve3D*> curves;

    // Создаем случайные кривые и добавляем их в контейнер curves
    for (int i = 0; i < 5; i++) {
        double choice = static_cast<double>(rand()) / RAND_MAX;

        if (choice < 0.33) {
            double x = static_cast<double>(rand()) / RAND_MAX * 10;
            double y = static_cast<double>(rand()) / RAND_MAX * 10;
            double z = static_cast<double>(rand()) / RAND_MAX * 10;
            double radius = static_cast<double>(rand()) / RAND_MAX * 5 + 1;
            curves.push_back(new Circle(x, y, z, radius));
        }
        else if (choice < 0.66) {
            double x = static_cast<double>(rand()) / RAND_MAX * 10;
            double y = static_cast<double>(rand()) / RAND_MAX * 10;
            double z = static_cast<double>(rand()) / RAND_MAX * 10;
            double semiMajorAxis = static_cast<double>(rand()) / RAND_MAX * 5 + 1;
            double semiMinorAxis = static_cast<double>(rand()) / RAND_MAX * 5 + 1;
            curves.push_back(new Ellipse(x, y, z, semiMajorAxis, semiMinorAxis));
        }
        else {
            double x = static_cast<double>(rand()) / RAND_MAX * 10;
            double y = static_cast<double>(rand()) / RAND_MAX * 10;
            double z = static_cast<double>(rand()) / RAND_MAX * 10;
            double semiMajorAxis = static_cast<double>(rand()) / RAND_MAX * 5 + 1;
            double semiMinorAxis = static_cast<double>(rand()) / RAND_MAX * 5 + 1;
            curves.push_back(new Spiral(x, y, z, semiMajorAxis, semiMinorAxis));
        }
    }

    // Выводим координаты точек и производные всех кривых в контейнере при t=PI/4
    double t = M_PI / 4;
    for (const auto& curve : curves) {
        std::cout << "Coordinates: (" << curve->evaluateX(t) << ", " << curve->evaluateY(t) << ", " << curve->evaluateZ(t) << ")" << std::endl;
        std::cout << "Derivative: (" << curve->derivativeX(t) << ", " << curve->derivativeY(t) << ", " << curve->derivativeZ(t) << ")" << std::endl;
    }

    // Создаем второй контейнер, который содержит только круги из первого контейнера
    std::vector<Circle*> circles;
    for (const auto& curve : curves) {
        if (dynamic_cast<Circle*>(curve)) {
            circles.push_back(static_cast<Circle*>(curve));
        }
    }

    // Сортируем второй контейнер в порядке возрастания радиусов окружностей
    std::sort(circles.begin(), circles.end(), [](Circle* a, Circle* b) {
        return a->radius() < b->radius();
        });

    // Вычисляем общую сумму радиусов всех кривых во втором контейнере
    double totalRadiusSum = 0.0;
    for (const auto& circle : circles) {
        totalRadiusSum += circle->radius();
    }

    std::cout << "Total radius sum: " << totalRadiusSum << std::endl;

    // Освобождаем память, выделенную для кривых
    for (const auto& curve : curves) {
        delete curve;
    }

    return 0;
}
