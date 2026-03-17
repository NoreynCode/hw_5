#include <iostream>

#include "rectangle.h"

namespace vector_editor {

    Rectangle::Rectangle(double x, double y, double width, double height)
        : m_width(width), m_height(height) {
        m_x = x;
        m_y = y;
    }

    void Rectangle::draw() const {
        std::cout << "Rect at (" << m_x << "," << m_y
            << ") " << m_width << "x" << m_height;
    }

    std::string Rectangle::type() const { return "Rect"; }

    Shape::Shared_ptr Rectangle::clone() const {
        return std::make_shared<Rectangle>(m_x, m_y, m_width, m_height);
    }
}