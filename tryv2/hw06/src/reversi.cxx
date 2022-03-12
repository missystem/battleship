#include "controller.hxx"

#include <stdexcept>
#include <string>


int
main(int argc, char *argv[]) {

    try {
        ///
        /// Don't change this command-line processing, as the grader
        /// will expect to be able to start your program this way.
        ///

        // You can change how you start your game class if you want
        // (but you probably don't need to):
        Controller(10, 10).run();

    } catch (std::exception const& e) {
        // This prints out error messages if, say, the command-line argument
        // cannot be parsed as `int`s.
        std::cerr << argv[0] << ": " << e.what() << "\n";
        return 1;
    }

    return 0;
}
