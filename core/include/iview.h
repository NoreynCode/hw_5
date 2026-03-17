#ifndef IVIEW
#define IVIEW

namespace vector_editor {

    class IView {
    public:
        virtual ~IView() = default;
        virtual void update() = 0;
    };
}
#endif // IVIEW