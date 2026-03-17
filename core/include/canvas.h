#ifndef CANVAS
#define CANVAS

#include <memory>

#include "iview.h"
#include "model.h"

namespace vector_editor {

    class Canvas : public IView {
    public:
        explicit Canvas(std::shared_ptr<Model> model);

        void update() override;
        void render() const;

    private:
        std::weak_ptr<Model> m_model;
    };
} 
#endif // CANVAS