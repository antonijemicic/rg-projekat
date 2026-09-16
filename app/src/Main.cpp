#include <app/MainApp.hpp>

#include <memory>

int main(int argc, char **argv) {
    return std::make_unique<app::MainApp>()->run(argc, argv);
}
