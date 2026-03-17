#ifndef LINE
#define LINE

#include "shape.h"

namespace vector_editor {

    class Line : public Shape {
    public:
        Line(double x1, double y1, double x2, double y2);

        void draw() const override;
        std::string type() const override;
        Shared_ptr clone() const override;

    private:
        double m_x2;
        double m_y2;
    };
}
#endif // LINE