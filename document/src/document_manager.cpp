#include <fstream>
#include <iostream>

#include "document_manager.h"

namespace vector_editor {

    bool DocumentManager::save_to_file(const Document::Shared_ptr& doc, const std::string& path) {
        std::ofstream file(path);
        if (!file.is_open()) {
            std::cout << "  Cannot create file\n";
            return false;
        }

        file << "Vector Editor Document\n";
        file << "Shapes: " << doc->size() << "\n";
        return true;
    }

    Document::Shared_ptr DocumentManager::load_from_file(const std::string& path) {
        std::ifstream file(path);
        if (!file.is_open()) {
            return nullptr;
        }
        return std::make_shared<Document>();
    }

    bool DocumentManager::export_to_format(const Document::Shared_ptr& doc, const std::string& path, const std::string& format) {
        if (format == "svg") {
            std::ofstream file(path);
            file << "<svg>\n";
            file << "  <!-- " << doc->size() << " shapes -->\n";
            file << "</svg>\n";
            std::cout << "  Exported to SVG\n";
            return true;
        }
        std::cout << "  Format not supported: " << format << "\n";
        return false;
    }

    Document::Shared_ptr DocumentManager::import_from_format(const std::string& /*path*/, const std::string& format) {
        if (format == "svg") {
            std::cout << "  Imported from SVG\n";
            return std::make_shared<Document>();
        }
        return nullptr;
    }
}