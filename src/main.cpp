#include <iostream>
#include <memory>

#include "editor.h"
#include "line.h"
#include "rectangle.h"
#include "circle.h"

namespace {

    std::unique_ptr<vector_editor::Editor> g_editor;

    void init() {
        g_editor = std::make_unique<vector_editor::Editor>();
        std::cout << ">> Editor Ready\n\n";
    }

    void on_new() {
        std::cout << "\n>> New document\n";
        g_editor->new_document();
    }

    void on_open(const std::string& path) {
        std::cout << "\n>> Open file: " << path << "\n";
        g_editor->load(path);
    }

    void on_save(const std::string& path) {
        std::cout << "\n>> Save to: " << path << "\n";
        g_editor->save(path);
    }

    void on_export(const std::string& path, const std::string& format) {
        std::cout << "\n>> Export as " << format << ": " << path << "\n";
        g_editor->export_to(path, format);
    }

    void on_add_line() {
        std::cout << "\n>> Add line\n";
        g_editor->add_shape(std::make_shared<vector_editor::Line>(50, 50, 250, 200));
    }

    void on_add_rect() {
        std::cout << "\n>> Add rectangle\n";
        g_editor->add_shape(std::make_shared<vector_editor::Rectangle>(100, 80, 180, 120));
    }

    void on_add_circle() {
        std::cout << "\n>> Add circle\n";
        g_editor->add_shape(std::make_shared<vector_editor::Circle>(200, 150, 60));
    }

    void on_delete(size_t idx) {
        std::cout << "\n>> Delete shape " << idx << "\n";
        g_editor->remove_shape(idx);
    }

    void on_exit() {
        std::cout << "\n>> Exit\n";
        g_editor.reset();
    }
}

int main() {
    
    init();
    on_new();
    on_add_line();
    on_add_rect();
    on_add_circle();
    on_save("drawing.txt");
    on_export("drawing.svg", "svg");
    on_delete(1);
    on_add_rect();
    on_open("drawing.txt");
    on_exit();

    return 0;
}