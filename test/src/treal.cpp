#include "json_real.hpp"
#include "json_integer.hpp"
#include <iostream>
#include <cassert>
#include <cmath>

#define RUN_TEST(test_func) do { std::cout << "[ RUN      ] " << #test_func << "\n"; test_func(); std::cout << "[       OK ] " << #test_func << "\n"; } while (0)

void test_real_positive() {
    // 1. Initializers
    json_real j_def;
    assert(j_def.is_real());

    json_real j_val(3.1415926535);
    assert(std::abs(j_val.value() - 3.1415926535) < 1e-9);

    // 2. Assignment Operator
    j_def = 2.71828;
    assert(std::abs(j_def.value() - 2.71828) < 1e-5);

    // 3. Copies
    json_real j_copy(j_val);
    assert(j_copy.value() == j_val.value());

    // 4. Converters
    json j_base = j_val;
    const json_real j_ref = json_as_real(j_base);
    assert(j_ref.value() == j_val.value());
}

void test_real_negative_casting() {
    json_integer j_int(42);
    bool caught = false;
    try {
        json_real bad_cast = json_as_real(j_int);
        (void)bad_cast;
    } catch (const std::bad_cast&) {
        caught = true;
    }
    assert(caught && "json_as_real failed to enforce runtime check constraint");
}

int main() {
    std::cout << "========================================\n";
    std::cout << "Running Unit Tests: json_real\n";
    std::cout << "========================================\n";
    RUN_TEST(test_real_positive);
    RUN_TEST(test_real_negative_casting);
    return 0;
}