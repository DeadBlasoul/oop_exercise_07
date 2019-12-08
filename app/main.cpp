#include "application.hpp"

oop::application g_application;

int main(const int argc, char* argv[]) {
    return g_application.start(argc, argv);
}
