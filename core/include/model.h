#ifndef MODEL
#define MODEL

#include <memory>
#include <string>

#include "document.h"

namespace vector_editor {

    class Model {
    public:
        Model();

        Document::Shared_ptr get_document() const;

        void new_document();
        bool import_document(const std::string& path);
        bool export_document(const std::string& path) const;

        void add_primitive(Shape::Shared_ptr primitive);
        bool remove_primitive(size_t index);

    private:
        Document::Shared_ptr m_document;
    };
}
#endif // MODEL