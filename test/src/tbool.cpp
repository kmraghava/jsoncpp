#include "json_bool.hpp"
#include "json_integer.hpp"
#include <iostream>
#include <cassert>

#define RUN_TEST(test_func) do { std::cout << "[ RUN      ] " << #test_func << "\n"; test_func(); std::cout << "[       OK ] " << #test_func << "\n"; } while (0)

void test_bool_positive() {
    // 1. Constructors & Data Types
    json_true jt;
    json_false jf;
    assert(jt.is_true());
    assert(jf.is_false());

    // 2. Copy Constructors
    json_true jt_copy(jt);
    json_false jf_copy(jf);
    assert(jt_copy.is_true());
    assert(jf_copy.is_false());

    // 3. String representations
    assert(jt.to_string() == "true");
    assert(jf.to_string() == "false");

    // 4. Global type conversion utility functions (References)
    json j_base_t = jt;
    json_true jt_ref = json_as_true(j_base_t);
    assert(jt_ref.is_true());

    json j_base_f = jf;
    const json_false jf_ref = json_as_false(j_base_f);
    assert(jf_ref.is_false());
}

void test_bool_negative_casting() {
    // Verifying that casting an invalid type using the helper utilities throws bad_cast
    json_integer j_int(1);
    
    bool caught_true_cast = false;
    try {
        json_true bad_ref = json_as_true(j_int);
        (void)bad_ref;
    } catch (const std::bad_cast&) {
        caught_true_cast = true;
    }
    assert(caught_true_cast && "json_as_true failed to throw std::bad_cast on non-bool type");

    bool caught_false_cast = false;
    try {
        const json_false bad_ref = json_as_false(j_int);
        (void)bad_ref;
    } catch (const std::bad_cast&) {
        caught_false_cast = true;
    }
    assert(caught_false_cast && "json_as_false failed to throw std::bad_cast on non-bool type");
}

int main() {
    std::cout << "========================================\n";
    std::cout << "Running Unit Tests: json_bool\n";
    std::cout << "========================================\n";
    RUN_TEST(test_bool_positive);
    RUN_TEST(test_bool_negative_casting);
    return 0;
}