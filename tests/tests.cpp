#define BOOST_TEST_MODULE VectorEditorTests
#include <boost/test/included/unit_test.hpp>
#include <boost/test/tools/output_test_stream.hpp>

#include <memory>
#include <sstream>
#include <string>

#include "editor.h"
#include "model.h"
#include "document.h"
#include "canvas.h"
#include "circle.h"
#include "line.h"
#include "rectangle.h"

namespace vector_editor {

    // Для проверки вывода
    class cout_redirect {
        std::streambuf* m_old;
    public:
        explicit cout_redirect(std::streambuf* new_buffer) : m_old(std::cout.rdbuf(new_buffer)) {}
        ~cout_redirect() { std::cout.rdbuf(m_old); }
    };

    // Полуморфизм
    BOOST_AUTO_TEST_SUITE(PolymorphismTests)

        BOOST_AUTO_TEST_CASE(test_shapes_draw_different_output) {
        std::vector<Shape::Shared_ptr> shapes;
        shapes.push_back(std::make_shared<Line>(10, 20, 30, 40));
        shapes.push_back(std::make_shared<Circle>(15, 25, 7));
        shapes.push_back(std::make_shared<Rectangle>(5, 10, 20, 30));

        boost::test_tools::output_test_stream output;
        cout_redirect guard(output.rdbuf());

        for (const auto& shape : shapes) {
            shape->draw();
            output << "\n";
        }

        std::string result = output.str();
       
        BOOST_CHECK(result.find("Line") != std::string::npos);
        BOOST_CHECK(result.find("Circle") != std::string::npos);
        BOOST_CHECK(result.find("Rect") != std::string::npos);
    }

    BOOST_AUTO_TEST_CASE(test_shape_clone_creates_independent_copy) {
        auto original = std::make_shared<Circle>(10, 20, 5);
        original->move_to(15, 25);

        auto copy = original->clone();

        // Разные объекты
        BOOST_CHECK_NE(original, copy);
        // С одинаковыми свойствами
        BOOST_CHECK_EQUAL(original->type(), copy->type());

        auto original_pos = original->position();
        auto copy_pos = copy->position();
        BOOST_CHECK_EQUAL(original_pos.first, copy_pos.first);
        BOOST_CHECK_EQUAL(original_pos.second, copy_pos.second);

        // Изменение оригинала не влияет на копию
        original->move_to(100, 100);
        copy_pos = copy->position();
        BOOST_CHECK_EQUAL(copy_pos.first, 15);
    }

    BOOST_AUTO_TEST_SUITE_END()

        //MVC
        BOOST_AUTO_TEST_SUITE(MVCTests)

        BOOST_AUTO_TEST_CASE(test_editor_add_shape_updates_view) {
        Editor editor;

        boost::test_tools::output_test_stream output;
        cout_redirect guard(output.rdbuf());

        // refresh() -> update() -> render()
        editor.add_shape(std::make_shared<Line>(0, 0, 10, 10));

        std::string result = output.str();
        // Рендер Canvas
        BOOST_CHECK(result.find("[Canvas]") != std::string::npos);
        BOOST_CHECK(result.find("Line") != std::string::npos);
    }

    BOOST_AUTO_TEST_CASE(test_model_holds_document_with_shapes) {
        Model model;

        // Фигуры через модель
        model.add_primitive(std::make_shared<Circle>(1, 2, 3));
        model.add_primitive(std::make_shared<Line>(4, 5, 6, 7));

        auto doc = model.get_document();
        BOOST_CHECK_EQUAL(doc->size(), 2);
        BOOST_CHECK_EQUAL(doc->get(0)->type(), "Circle");
        BOOST_CHECK_EQUAL(doc->get(1)->type(), "Line");
    }

    BOOST_AUTO_TEST_SUITE_END()

        // Документы
        BOOST_AUTO_TEST_SUITE(DocumentManagementTests)

        BOOST_AUTO_TEST_CASE(test_document_add_remove_shapes) {
        Document doc;

        // Добавление
        doc.add(std::make_shared<Rectangle>(0, 0, 10, 10));
        doc.add(std::make_shared<Circle>(5, 5, 3));
        BOOST_CHECK_EQUAL(doc.size(), 2);

        // Удаление
        bool result = doc.remove(0);
        BOOST_CHECK(result);
        BOOST_CHECK_EQUAL(doc.size(), 1);
        BOOST_CHECK_EQUAL(doc.get(0)->type(), "Circle");

        // Очистка
        doc.clear();
        BOOST_CHECK_EQUAL(doc.size(), 0);
    }

    BOOST_AUTO_TEST_CASE(test_model_new_document_creates_empty_doc) {
        Model model;
        model.add_primitive(std::make_shared<Line>(0, 0, 1, 1));
        BOOST_CHECK_EQUAL(model.get_document()->size(), 1);

        model.new_document();

        auto new_doc = model.get_document();
        BOOST_CHECK_EQUAL(new_doc->size(), 0);
    }

    BOOST_AUTO_TEST_SUITE_END()

        // Граничные случаи
        BOOST_AUTO_TEST_SUITE(EdgeCasesTests)

        BOOST_AUTO_TEST_CASE(test_remove_nonexistent_shape) {
        Document doc;
        doc.add(std::make_shared<Line>(0, 0, 1, 1));

        // Несуществующий индекс
        bool result = doc.remove(10); 
        BOOST_CHECK(!result);
        BOOST_CHECK_EQUAL(doc.size(), 1);
    }

    BOOST_AUTO_TEST_CASE(test_canvas_without_model) {
        Canvas canvas(nullptr);

        boost::test_tools::output_test_stream output;
        cout_redirect guard(output.rdbuf());

        canvas.render();

        std::string result = output.str();
        BOOST_CHECK(result.find("[Canvas]") != std::string::npos);
    }

    BOOST_AUTO_TEST_SUITE_END()
} 