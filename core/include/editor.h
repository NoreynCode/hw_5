#ifndef EDITOR
#define EDITOR

#include <memory>
#include <string>

#include "model.h"
#include "iview.h"
#include "shape.h"

namespace vector_editor {

    class Editor {
    public:
        Editor();

        void new_document();
        bool load(const std::string& path);
        bool save(const std::string& path) const;
        bool export_to(const std::string& path, const std::string& format);
        bool import_from(const std::string& path, const std::string& format);

        void add_shape(Shape::Shared_ptr shape);
        bool remove_shape(size_t index);

        void refresh();
        void polymorphism() const;

    private:
        std::shared_ptr<Model> m_model;
        std::shared_ptr<IView> m_view;
    };
}
#endif // EDITOR