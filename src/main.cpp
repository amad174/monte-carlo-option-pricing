#include <iostream>
#include <random>
#include <cmath>

double simulate_terminal_price(double S0, double r, double sigma, double T, double Z) {
    double drift = (r - 0.5 * sigma * sigma) * T;
    double diffusion = sigma * std::sqrt(T) * Z;
    return S0 * std::exp(drift + diffusion);
}

int main() {
    std::mt19937 rng(42);
    std::normal_distribution<double> normal(0.0, 1.0);

    double S0 = 100.0; // Initial stock price
    double r = 0.05;   // Risk-free rate
    double sigma = 0.9; // Volatility
    double T = 1.0;    // Time to maturity in years

    for (int i = 0; i < 5; ++i) {
        double Z = normal(rng);
        double ST = simulate_terminal_price(S0, r, sigma, T, Z);

        std::cout << "Z=" << Z << " -> ST=" << ST << "\n";
        
    }
    return 0;
}