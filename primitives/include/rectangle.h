#ifndef RECTANGLE
#define RECTANGLE

#include "shape.h"

namespace vector_editor {

    class Rectangle : public Shape {
    public:
        Rectangle(double x, double y, double width, double height);

        void draw() const override;
        std::string type() const override;
        Shared_ptr clone() const override;

    private:
        double m_width;
        double m_height;
    };
}
#endif // RECTANGLE