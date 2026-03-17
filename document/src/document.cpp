#include "document.h"

namespace vector_editor {

    void Document::add(Shape::Shared_ptr shape) {
        if (shape) {
            m_shapes.push_back(shape);
        }
    }

    bool Document::remove(size_t index) {
        if (index < m_shapes.size()) {
            m_shapes.erase(m_shapes.begin() + index);
            return true;
        }
        return false;
    }

    void Document::clear() {
        m_shapes.clear();
    }

    size_t Document::size() const {
        return m_shapes.size();
    }

    Shape::Shared_ptr Document::get(size_t index) const {
        if (index < m_shapes.size()) {
            return m_shapes[index];
        }
        return nullptr;
    }

    const std::vector<Shape::Shared_ptr>& Document::all() const {
        return m_shapes;
    }
}