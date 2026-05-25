#include "json_base.hpp"
#include "json_string.hpp"
#include "json_integer.hpp"
#include "json_bool.hpp"
#include <iostream>
#include <cassert>

// Simple helper macro for clear test logging
#define RUN_TEST(test_func) \
    do { \
        std::cout << "[ RUN      ] " << #test_func << "\n"; \
        test_func(); \
        std::cout << "[       OK ] " << #test_func << "\n"; \
    } while (0)

// ============================================================================
// POSITIVE TEST CASES
// ============================================================================

void test_default_constructor() {
    json j;
    // By default, an empty/uninitialized variant wrapper should report unknown
    assert(j.is_unknown());
    assert(!j.is_string());
    assert(!j.is_real());
    assert(!j.is_integer());
    assert(!j.is_bool());
    assert(!j.is_array());
    assert(!j.is_object());
}

void test_copy_and_assignment() {
    // Assuming derived classes instantiate m_obj_p properly
    json_integer j1(42);
    
    // Test Copy Constructor
    json j2(j1);
    assert(j2.is_integer());
    assert(j2 == j1);

    // Test Copy Assignment
    json j3;
    j3 = j2;
    assert(j3.is_integer());
    assert(j3 == j2);
}

void test_type_checking() {
    json_string s("hello");
    assert(s.is_string());
    assert(!s.is_integer());

    json_true t;
    assert(t.is_true());
    assert(t.is_bool());
    assert(!t.is_false());

    json_false f;
    assert(f.is_false());
    assert(f.is_bool());
    assert(!f.is_true());
}

void test_equality_operators() {
    json_integer a(100);
    json_integer b(100);
    json_integer c(200);
    json_string d("100");

    json_integer e = a;

    // Positive equality
    assert(a == e);
    assert(a != b);
    assert(a.equals(b));

    // Positive inequality (same type, different value)
    assert(a != c);
    
    // Positive inequality (different type, matching literal representation)
    assert(a != d); 
}

// ============================================================================
// NEGATIVE / EDGE TEST CASES
// ============================================================================

void test_uninitialized_operations() {
    json j1; // Unknown / null state
    json j2;

    // Two uninitialized base objects should technically be structurally equal (both null)
    // or handled safely without crashing.
    try {
        bool eq = (j1 == j2);
        std::cout << "  Info: Uninitialized comparison completed. Equal = " << (eq ? "true" : "false") << "\n";
    } catch (const std::exception& e) {
        std::cerr << "  FAIL: Exception thrown during uninitialized comparison: " << e.what() << "\n";
        assert(false);
    }

    // Calling to_string() on an empty variant wrapper shouldn't crash.
    try {
        std::string s = j1.to_string();
        std::cout << "  Info: Uninitialized to_string output: \"" << s << "\"\n";
    } catch (const std::exception& e) {
        std::cerr << "  FAIL: Exception thrown during uninitialized to_string(): " << e.what() << "\n";
        assert(false);
    }
}

void test_cross_type_equality_negative() {
    json_string s("false");
    json_false f;

    // Even though the string contents match the literal value of the boolean, 
    // type checking within equals() should reject it.
    assert(!(s == f));
    assert(s != f);
}

// ============================================================================
// MAIN RUNNER
// ============================================================================

int main() {
    std::cout << "========================================\n";
    std::cout << "Running Unit Tests for Class: json (Base)\n";
    std::cout << "========================================\n";

    RUN_TEST(test_default_constructor);
    RUN_TEST(test_copy_and_assignment);
    RUN_TEST(test_type_checking);
    RUN_TEST(test_equality_operators);
    RUN_TEST(test_uninitialized_operations);
    RUN_TEST(test_cross_type_equality_negative);

    std::cout << "========================================\n";
    std::cout << "All tests for json (Base) passed successfully!\n";
    std::cout << "========================================\n";
    return 0;
}