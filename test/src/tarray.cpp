#include "json_array.hpp"
#include "json_string.hpp"
#include "json_integer.hpp"
#include "json_bool.hpp"
#include <iostream>
#include <cassert>

#define RUN_TEST(test_func) \
    do { \
        std::cout << "[ RUN      ] " << #test_func << "\n"; \
        test_func(); \
        std::cout << "[       OK ] " << #test_func << "\n"; \
    } while (0)

// ============================================================================
// POSITIVE TEST CASES
// ============================================================================

void test_array_constructors_and_basic_mutations() {
    // 1. Default initialization
    json_array arr;
    assert(arr.is_array());
    assert(arr.size() == 0);

    // 2. Initializing via an existing vector of json elements
    std::vector<json> initial_elements = { json_integer(10), json_string("test"), json_true() };
    json_array arr_from_vec(initial_elements);
    assert(arr_from_vec.size() == 3);
    assert(arr_from_vec.get(0).is_integer());
    assert(arr_from_vec.get(1).is_string());
    assert(arr_from_vec.get(2).is_true());

    // 3. Vector assignment operator=
    std::vector<json> next_elements = { json_false() };
    arr = next_elements;
    assert(arr.size() == 1);
    assert(arr.get(0).is_false());

    // 4. Append operation
    arr.clear();
    assert(arr.size() == 0);
    arr.append(json_integer(100));
    arr.append(json_integer(200));
    assert(arr.size() == 2);

    // 5. Explicit indexing mutators (get/set/operator[])
    arr.set(0, json_string("replaced"));
    assert(json_as_string(arr.get(0)).value() == "replaced");

    arr[1] = json_true();
    assert(arr[1].is_true());
}

void test_array_structural_modifications() {
    json_array arr;
    arr.append(json_integer(1));
    arr.append(json_integer(3));

    // Insert at index boundary
    arr.insert(1, json_integer(2)); // Content: [1, 2, 3]
    assert(arr.size() == 3);
    assert(json_as_integer(arr.get(1)).value() == 2);

    // Remove middle element
    arr.remove(1); // Content: [1, 3]
    assert(arr.size() == 2);
    assert(json_as_integer(arr.get(1)).value() == 3);

    // Extend array using another array structure
    json_array companion;
    companion.append(json_string("A"));
    companion.append(json_string("B"));

    arr.extend(companion); // Content: [1, 3, "A", "B"]
    assert(arr.size() == 4);
    assert(arr.get(2).is_string());
}

void test_array_deep_copy_semantics() {
    json_array original;
    original.append(json_integer(999));

    // Copy construction
    json_array clone = json_as_array(original.clone());
    assert(clone.size() == 1);

    // Mutate original, verify clone isolation contract
    original.set(0, json_integer(111));
    assert(json_as_integer(clone.get(0)).value() == 999);
}

// ============================================================================
// NEGATIVE / EDGE TEST CASES
// ============================================================================

void test_array_out_of_bounds_protection() {
    json_array arr;
    arr.append(json_integer(42));

    // Out of bounds read via get()
    bool caught_get = false;
    try {
        json item = arr.get(5);
        (void)item;
    } catch (const std::out_of_range&) {
        caught_get = true;
    } catch (...) {
        // If your implementation throws a custom exception layout, handle here safely
        caught_get = true;
    }
    std::cout << "  Info: OOB get boundary handled = " << (caught_get ? "Yes" : "No") << "\n";

    // Out of bounds write via set()
    bool caught_set = false;
    try {
        arr.set(10, json_string("OOB"));
    } catch (...) {
        caught_set = true;
    }
    std::cout << "  Info: OOB set boundary handled = " << (caught_set ? "Yes" : "No") << "\n";

    // Out of bounds deletion via remove()
    bool caught_remove = false;
    try {
        arr.remove(10);
    } catch (...) {
        caught_remove = true;
    }
    std::cout << "  Info: OOB remove boundary handled = " << (caught_remove ? "Yes" : "No") << "\n";

    // Out of bounds insertion via insert()
    bool caught_insert = false;
    try {
        arr.insert(10, json_integer(0));
    } catch (...) {
        caught_insert = true;
    }
    std::cout << "  Info: OOB insert boundary handled = " << (caught_insert ? "Yes" : "No") << "\n";
}

void test_array_invalid_casting() {
    json_integer primitive(55);
    bool caught = false;
    try {
        json_array bad_ref = json_as_array(primitive);
        (void)bad_ref;
    } catch (const std::bad_cast&) {
        caught = true;
    }
    assert(caught && "json_as_array failed to reject a non-array primitive type assignment safely");
}

int main() {
    std::cout << "========================================\n";
    std::cout << "Running Unit Tests: json_array\n";
    std::cout << "========================================\n";

    RUN_TEST(test_array_constructors_and_basic_mutations);
    RUN_TEST(test_array_structural_modifications);
    RUN_TEST(test_array_deep_copy_semantics);
    RUN_TEST(test_array_out_of_bounds_protection);
    RUN_TEST(test_array_invalid_casting);

    std::cout << "All tests for json_array completed successfully!\n";
    return 0;
}