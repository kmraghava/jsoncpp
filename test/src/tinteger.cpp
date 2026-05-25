#include "json_integer.hpp"
#include "json_string.hpp"
#include <iostream>
#include <cassert>
#include <climits>

#define RUN_TEST(test_func) do { std::cout << "[ RUN      ] " << #test_func << "\n"; test_func(); std::cout << "[       OK ] " << #test_func << "\n"; } while (0)

void test_integer_positive() {
    // 1. Default initialization (should cleanly resolve to 0 or safe state)
    json_integer j_default;
    assert(j_default.is_integer());
    
    // 2. Explicit Value Assignment & Access
    json_integer j_val(123456);
    assert(j_val.value() == 123456);

    // 3. Assignment operator (long)
    j_default = 7890L;
    assert(j_default.value() == 7890);

    // 4. Copy Construction
    json_integer j_copy(j_val);
    assert(j_copy.value() == 123456);

    // 5. Utility conversion reference methods
    json j_base = j_val;
    json_integer j_ref = json_as_integer(j_base);
    assert(j_ref.value() == 123456);
}

void test_integer_boundaries() {
    // Testing extreme limits of a standard signed long system layout
    json_integer j_max(LONG_MAX);
    assert(j_max.value() == LONG_MAX);

    json_integer j_min(LONG_MIN);
    assert(j_min.value() == LONG_MIN);
}

void test_integer_negative_casting() {
    json_string j_str("123");
    bool caught = false;
    try {
        json_integer bad_ref = json_as_integer(j_str);
        (void)bad_ref;
    } catch (const std::bad_cast&) {
        caught = true;
    }
    assert(caught && "json_as_integer failed to throw std::bad_cast on mismatching string variant");
}

int main() {
    std::cout << "========================================\n";
    std::cout << "Running Unit Tests: json_integer\n";
    std::cout << "========================================\n";
    RUN_TEST(test_integer_positive);
    RUN_TEST(test_integer_boundaries);
    RUN_TEST(test_integer_negative_casting);
    return 0;
}