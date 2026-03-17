#include <iostream>

#include "canvas.h"

namespace vector_editor {

    Canvas::Canvas(std::shared_ptr<Model> model) : m_model(model) {}

    void Canvas::update() {
        render();
    }

    void Canvas::render() const {
        std::cout << "\n[Canvas]\n";

        if (auto model = m_model.lock()) {
            auto doc = model->get_document();

            if (doc->size() == 0) {
                std::cout << "  Empty\n";
            }
            else {
                std::cout << "  " << doc->size() << " shape(s):\n";
                for (size_t i = 0; i < doc->size(); ++i) {
                    std::cout << "  " << i << ": ";
                    if (auto shape = doc->get(i)) {
                        shape->draw();
                        std::cout << "\n";
                    }
                }
            }
        }
    }
}