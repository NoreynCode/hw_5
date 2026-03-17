#ifndef DOCUMENT
#define DOCUMENT

#include <vector>
#include <memory>

#include "shape.h"

namespace vector_editor {

    class Document {
    public:
        using Shared_ptr = std::shared_ptr<Document>;

        void add(Shape::Shared_ptr shape);
        bool remove(size_t index);
        void clear();

        size_t size() const;
        Shape::Shared_ptr get(size_t index) const;
        const std::vector<Shape::Shared_ptr>& all() const;

    private:
        std::vector<Shape::Shared_ptr> m_shapes;
    };
}
#endif // DOCUMENT