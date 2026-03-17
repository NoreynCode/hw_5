#ifndef SHAPE
#define SHAPE

#include <memory>
#include <string>
#include <utility>

namespace vector_editor {

    class Shape {
    public:
        using Shared_ptr = std::shared_ptr<Shape>;
        using Weak_ptr = std::weak_ptr<Shape>;

        virtual ~Shape();

        virtual void draw() const = 0;
        virtual std::string type() const = 0;
        virtual Shared_ptr clone() const = 0;

        void move_to(double x, double y);
        std::pair<double, double> position() const;

    protected:
        double m_x = 0.0;
        double m_y = 0.0;
    };
}
#endif // SHAPE