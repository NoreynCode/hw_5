#include <iostream>
#include <cmath>

#include "line.h"

namespace vector_editor {

    Line::Line(double x1, double y1, double x2, double y2)
        : m_x2(x2), m_y2(y2) {
        m_x = x1;
        m_y = y1;
    }

    void Line::draw() const {
        double len = std::sqrt((m_x2 - m_x) * (m_x2 - m_x) + (m_y2 - m_y) * (m_y2 - m_y));
        std::cout << "Line (" << m_x << "," << m_y << ")-("
            << m_x2 << "," << m_y2 << ") len=" << len;
    }

    std::string Line::type() const { return "Line"; }

    Shape::Shared_ptr Line::clone() const {
        return std::make_shared<Line>(m_x, m_y, m_x2, m_y2);
    }
}