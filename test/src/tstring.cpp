#include "json_string.hpp"
#include "json_bool.hpp"
#include <iostream>
#include <cassert>

#define RUN_TEST(test_func) do { std::cout << "[ RUN      ] " << #test_func << "\n"; test_func(); std::cout << "[       OK ] " << #test_func << "\n"; } while (0)

void test_string_positive() {
    // 1. Default constructor
    json_string j_def;
    assert(j_def.length() == 0);
    assert(j_def.value() == "");

    // 2. Standard string initialization
    std::string source = "Cambium Networks";
    json_string j_str1(source);
    assert(j_str1.value() == source);
    assert(j_str1.length() == source.length());

    // 3. raw C-string construction
    json_string j_str2("Embedded Systems");
    assert(j_str2.value() == "Embedded Systems");

    // 4. Substring raw pointer initialization with explicit length size
    json_string j_str3("TruncateThisBuffer", 8);
    assert(j_str3.value() == "Truncate");
    assert(j_str3.length() == 8);

    // 5. Mutator sets
    j_def.set(std::string("New Value"));
    assert(j_def.value() == "New Value");

    j_def.set("C-Str Override");
    assert(j_def.value() == "C-Str Override");

    j_def.set("BufferRangeTest", 6);
    assert(j_def.value() == "Buffer");

    // 6. Assignment operators
    j_def = std::string("Operator Assign");
    assert(j_def.value() == "Operator Assign");

    j_def = "Literal Assign";
    assert(j_def.value() == "Literal Assign");
}

void test_string_edge_cases() {
    // Empty strings and explicit zero lengths
    json_string j_empty("");
    assert(j_empty.length() == 0);
    assert(j_empty.value().empty());

    json_string j_zero_len("Data", 0);
    assert(j_zero_len.length() == 0);
    assert(j_zero_len.value() == "");
}

void test_string_negative_casting() {
    json_true j_true_obj;
    bool caught = false;
    try {
        json_string bad_ref = json_as_string(j_true_obj);
        (void)bad_ref;
    } catch(const std::bad_cast&) {
        caught = true;
    }
    assert(caught && "json_as_string did not reject base variant types safely");
}

int main() {
    std::cout << "========================================\n";
    std::cout << "Running Unit Tests: json_string\n";
    std::cout << "========================================\n";
    RUN_TEST(test_string_positive);
    RUN_TEST(test_string_edge_cases);
    RUN_TEST(test_string_negative_casting);
    return 0;
}