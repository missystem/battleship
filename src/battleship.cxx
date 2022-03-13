#include "controller.hxx"

#include <stdexcept>
#include <string>


int
main(int argc, char *argv[]) {

    try {
        Controller(10, 10).run();

    } catch (std::exception const& e) {
        std::cerr << argv[0] << ": " << e.what() << "\n";
        return 1;
    }

    return 0;
}
