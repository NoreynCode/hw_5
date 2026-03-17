#ifndef CIRCLE
#define CIRCLE

#include "shape.h"

namespace vector_editor {

    class Circle : public Shape {
    public:
        Circle(double x, double y, double radius);

        void draw() const override;
        std::string type() const override;
        Shared_ptr clone() const override;

    private:
        double m_radius;
    };
}
#endif // CIRCLE