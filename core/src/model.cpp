#include <iostream>

#include "model.h"
#include "document_manager.h"

namespace vector_editor {

    Model::Model() : m_document(std::make_shared<Document>()) {}

    Document::Shared_ptr Model::get_document() const {
        return m_document;
    }

    void Model::new_document() {
        m_document = std::make_shared<Document>();
        std::cout << "  New document created\n";
    }

    bool Model::import_document(const std::string& path) {
        std::cout << "  Loading from " << path << "... ";
        auto doc = DocumentManager::load_from_file(path);
        if (!doc) {
            std::cout << "failed\n";
            return false;
        }
        m_document = doc;
        std::cout << "ok (" << doc->size() << " shapes)\n";
        return true;
    }

    bool Model::export_document(const std::string& path) const {
        std::cout << "  Saving to " << path << "... ";
        bool result = DocumentManager::save_to_file(m_document, path);
        std::cout << (result ? "ok" : "failed") << "\n";
        return result;
    }

    void Model::add_primitive(Shape::Shared_ptr primitive) {
        if (primitive) {
            m_document->add(primitive);
            std::cout << "  Added " << primitive->type() << "\n";
        }
    }

    bool Model::remove_primitive(size_t index) {
        if (index < m_document->size()) {
            m_document->remove(index);
            std::cout << "  Removed shape " << index << "\n";
            return true;
        }
        std::cout << "  Cannot remove shape " << index << "\n";
        return false;
    }
}