#include <iostream>

#include "editor.h"
#include "canvas.h"
#include "line.h"
#include "rectangle.h"
#include "circle.h"
#include "document_manager.h"

namespace vector_editor {

    Editor::Editor()
        : m_model(std::make_shared<Model>())
        , m_view(std::make_shared<Canvas>(m_model))
    {
    }

    void Editor::new_document() {
        m_model->new_document();
        refresh();
    }

    bool Editor::load(const std::string& path) {
        if (m_model->import_document(path)) {
            refresh();
            return true;
        }
        return false;
    }

    bool Editor::save(const std::string& path) const {
        return m_model->export_document(path);
    }

    bool Editor::export_to(const std::string& path, const std::string& format) {
        return DocumentManager::export_to_format(m_model->get_document(), path, format);
    }

    bool Editor::import_from(const std::string& path, const std::string& format) {
        auto doc = DocumentManager::import_from_format(path, format);
        if (!doc) return false;
        refresh();
        return true;
    }


    void Editor::add_shape(Shape::Shared_ptr shape) {
        m_model->add_primitive(shape);
        refresh();
    }

    bool Editor::remove_shape(size_t index) {
        if (m_model->remove_primitive(index)) {
            refresh();
            return true;
        }
        return false;
    }

    void Editor::refresh() {
        m_view->update();
    }

    // Это только для примера
    void Editor::polymorphism() const {
        std::cout << "Polymorphism { \n";

        Shape::Shared_ptr shapes[] = {
            std::make_shared<Line>(10, 20, 150, 180),
            std::make_shared<Rectangle>(30, 40, 200, 100),
            std::make_shared<Circle>(100, 100, 50)
        };

        for (const auto& s : shapes) {
            std::cout << "  " << s->type() << ": ";
            s->draw();
            std::cout << "\n";
        }
        std::cout << " }\n";
    }
}