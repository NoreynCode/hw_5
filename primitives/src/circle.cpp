#include <iostream>

#include "circle.h"

namespace vector_editor {

    Circle::Circle(double x, double y, double radius) : m_radius(radius) {
        m_x = x;
        m_y = y;
    }

    void Circle::draw() const {
        std::cout << "Circle at (" << m_x << "," << m_y
            << ") r=" << m_radius;
    }

    std::string Circle::type() const { return "Circle"; }

    Shape::Shared_ptr Circle::clone() const {
        return std::make_shared<Circle>(m_x, m_y, m_radius);
    }
}