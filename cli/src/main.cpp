#include <fbm/fbm.hpp>
#include <fbm/generate_normal_random.hpp>
#include <iostream>
#include <fstream>
#include <chrono>

int main(int argc, char** argv) {
    if (argc != 5) {
        std::cout << "Usage\n\n\t" << argv[0] << " <dim> <nx> <H> <outfile.txt>\n\n"
                  << "\t\t - dim==3 for now\n"
                  << "\t\t - nx is the number of cells in one direction (must be power of 2)\n"
                  << "\t\t - 0<H<1 is the Hurst index,\n"
                  << "\t\t - outfile.txt is the output file (will be numpy.loadtxt compatible)\n\n"
                  << "Note that the text file will be in one dimension, you have to reshape it yourself."
                  <<"\n\nWill write the total elapsed time of generating the brownian bridge (without IO or generation of uniform random numbers)"
                 << std::endl;

        return EXIT_FAILURE;
    }

    const int dim = std::atoi(argv[1]);

    if (dim != 3) {
        std::cerr << "dimension must be 3" << std::endl;
        return EXIT_FAILURE;
    }

    const int nx = std::atoi(argv[2]);

    const double H = std::atof(argv[3]);

    const std::string outfilename(argv[4]);


    auto X = fbm::generate_normal_random((nx+1)*(nx+1)*(nx+1));

    auto start_time = std::chrono::high_resolution_clock::now();
    auto fractional_bridge = fbm::fractional_brownian_bridge_3d(H, nx, X);
    auto end_time = std::chrono::high_resolution_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count() << std::endl;

    std::ofstream output_file(outfilename);

    for (const auto d : fractional_bridge) {
        output_file << d << "\n";
    }


}
