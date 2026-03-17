#ifndef DOCUMENT_MANAGER
#define DOCUMENT_MANAGER

#include <string>
#include <memory>

#include "document.h"

namespace vector_editor {

    class DocumentManager {
    public:
        static bool save_to_file(const Document::Shared_ptr& doc, const std::string& path);
        static Document::Shared_ptr load_from_file(const std::string& path);

        static bool export_to_format(const Document::Shared_ptr& doc, const std::string& path, const std::string& format);
        static Document::Shared_ptr import_from_format(const std::string& path, const std::string& format);
    };
}
#endif // DOCUMENT_MANAGER