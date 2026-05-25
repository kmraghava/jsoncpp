#include "json_object.hpp"
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

void test_object_constructors_and_basic_crud() {
    // 1. Constructor Initialization
    json_object obj;
    assert(obj.is_object());
    assert(obj.size() == 0);

    // 2. Insertion and Existence (std::string and const char* variants)
    obj.set("string_key", json_string("value1"));
    std::string key_std = "int_key";
    obj.set(key_std, json_integer(42));

    assert(obj.size() == 2);
    assert(obj.exists("string_key"));
    assert(obj.exists(key_std));

    // 3. Retrieval checks (get() & operator[])
    assert(obj.get("string_key").is_string());
    assert(json_as_string(obj.get("string_key")).value() == "value1");
    
    assert(obj[key_std].is_integer());
    assert(json_as_integer(obj[key_std]).value() == 42);

    // 4. In-place modification through operator[] reference layout
    obj["int_key"] = json_integer(100);
    assert(json_as_integer(obj.get("int_key")).value() == 100);

    // 5. Erasure verification
    obj.del("string_key");
    assert(!obj.exists("string_key"));
    assert(obj.size() == 1);

    obj.clear();
    assert(obj.size() == 0);
}

void test_object_copy_semantics() {
    json_object original;
    original.set("shared", json_integer(5));

    json_object clone = json_as_object(original.clone());
    assert(clone.exists("shared"));

    // Verify deep separation isolation properties
    original.set("shared", json_integer(99));
    assert(json_as_integer(clone.get("shared")).value() == 5);
}

void test_object_update_policies() {
    // This suite ensures that the precise combinations of updates do not overlap or break
    json_object base;
    base.set("target_alpha", json_string("original_alpha"));
    base.set("target_beta",  json_string("original_beta"));

    json_object incoming;
    incoming.set("target_beta",  json_string("incoming_beta"));
    incoming.set("target_gamma", json_string("incoming_gamma"));

    // Scenario A: update_missing (only keys missing from base should transfer)
    json_object test_missing = json_as_object(base.clone());
    test_missing.update_missing(incoming);
    assert(json_as_string(test_missing.get("target_beta")).value() == "original_beta"); // Kept
    assert(test_missing.exists("target_gamma"));                                       // Added

    // Scenario B: update_existing (only common shared properties change)
    json_object test_existing = json_as_object(base.clone());
    test_existing.update_existing(incoming);
    assert(json_as_string(test_existing.get("target_beta")).value() == "incoming_beta"); // Changed
    assert(!test_existing.exists("target_gamma"));                                      // Ignored

    // Scenario C: standard update (unconditional overwrite & append extension)
    json_object test_standard = json_as_object(base.clone());
    test_standard.update(incoming);
    assert(json_as_string(test_standard.get("target_beta")).value() == "incoming_beta");
    assert(test_standard.exists("target_gamma"));

    // Scenario D: update_recursive (nested dictionary structural deep evaluation)
    json_object nested_base;
    json_object inner_base;
    inner_base.set("inner_key1", json_string("inner_val1"));
    nested_base.set("nested_node", inner_base);

    json_object nested_incoming;
    json_object inner_incoming;
    inner_incoming.set("inner_key2", json_string("inner_val2"));
    nested_incoming.set("nested_node", inner_incoming);

    nested_base.update_recursive(nested_incoming);
    
    // Extract merged object properties recursively
    json_object merged_inner = json_as_object(nested_base.get("nested_node"));
    assert(merged_inner.exists("inner_key1"));
    assert(merged_inner.exists("inner_key2"));
}

// ============================================================================
// NEGATIVE / EDGE TEST CASES
// ============================================================================

void test_object_missing_keys_and_edge_behaviours() {
    json_object obj;

    // Behavioral exploration for nonexistent keys with const getters
    // Note: Some engines return an UNKNOWN variant node, others assert or throw. 
    try {
        json missing_item = obj.get("non_existent_key");
        std::cout << "  Info: Non-existent key get returned variant type: " << "\n";
    } catch (...) {
        std::cout << "  Info: Exception thrown upon accessing missing key via get().\n";
    }

    // Behavioral exploration for non-existent operators[] mutations
    // operator[] typically inserts a default uninitialized node matching maps contract
    json& default_inserted = obj["auto_insert"];
    (void)default_inserted;
    assert(obj.exists("auto_insert"));

    // Safe protection from invalid deletion targets
    try {
        obj.del("phantom_key_that_doesnt_exist");
    } catch (...) {
        std::cerr << "  FAIL: del() threw an exception on a non-existent key.\n";
        assert(false);
    }
}

void test_object_invalid_casting() {
    json_string primitive("not_an_obj");
    bool caught = false;
    try {
        json_object bad_ref = json_as_object(primitive);
        (void)bad_ref;
    } catch (const std::bad_cast&) {
        caught = true;
    }
    assert(caught && "json_as_object failed to trap runtime cross-casting exceptions cleanly");
}

int main() {
    std::cout << "========================================\n";
    std::cout << "Running Unit Tests: json_object\n";
    std::cout << "========================================\n";

    RUN_TEST(test_object_constructors_and_basic_crud);
    RUN_TEST(test_object_copy_semantics);
    RUN_TEST(test_object_update_policies);
    RUN_TEST(test_object_missing_keys_and_edge_behaviours);
    RUN_TEST(test_object_invalid_casting);

    std::cout << "All tests for json_object completed successfully!\n";
    return 0;
}