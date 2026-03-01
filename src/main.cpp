#include <iostream>
#include <random>

int main() {
    std::mt19937 rng(42);
    std::normal_distribution<double> normal(0.0, 1.0);

    for (int i = 0; i < 5; ++i) {
        double z = normal(rng);
        std::cout << "Z[" << i << "] = " << z << "\n";
        
    }
    return 0;
}