#include "shape.h"

namespace vector_editor {

    Shape::~Shape() = default;

    void Shape::move_to(double x, double y) {
        m_x = x;
        m_y = y;
    }

    std::pair<double, double> Shape::position() const {
        return { m_x, m_y };
    }
}