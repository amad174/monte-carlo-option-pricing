#include <iostream>
#include <random>
#include <cmath>
#include <algorithm>

double simulate_terminal_price(double S0, double r, double sigma, double T, double Z) {
    double drift = (r - 0.5 * sigma * sigma) * T;
    double diffusion = sigma * std::sqrt(T) * Z;
    return S0 * std::exp(drift + diffusion);
}

double call_payoff(double ST, double K) {
    return std::max(ST - K, 0.0);
}

double normal_cdf(double x) {
    return 0.5 * std::erfc(-x / std::sqrt(2));
}

double black_scholes_call(double S0, double K, double r, double sigma, double T) {

    double d1 = (std::log(S0 / K) + (r + 0.5 * sigma * sigma) * T)
                / (sigma * std::sqrt(T));

    double d2 = d1 - sigma * std::sqrt(T);

    return S0 * normal_cdf(d1)
           - K * std::exp(-r * T) * normal_cdf(d2);
}

int main() {
    std::mt19937 rng(42);
    std::normal_distribution<double> normal(0.0, 1.0);

    double S0 = 100.0; // Initial stock price
    double r = 0.05;   // Risk-free rate
    double sigma = 0.2; // Volatility
    double T = 1.0;    // Time to maturity in years
    double K = 100.0; // Strike price

    double payoff_sum = 0.0; // Payoff Accumulator
    int N = 100000;

    for (int i = 0; i < N; ++i) {
        double Z = normal(rng);
        double ST = simulate_terminal_price(S0, r, sigma, T, Z);
        double payoff = call_payoff(ST, K);

        payoff_sum += payoff;
    }

    double average_payoff = payoff_sum / N;
    double option_price = std::exp(-r * T) * average_payoff; // Discounting the average payoff back to present value

    double bs_price = black_scholes_call(S0, K, r, sigma, T);

    std::cout << "Monte Carlo Price: " << option_price << "\n";
    std::cout << "Black-Scholes Price: " << bs_price << "\n";
    std::cout << "Difference: " << std::abs(option_price - bs_price) << "\n";
    
    return 0;
}