#!/bin/sh

SCRIPT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)

SUITES_DIR="$SCRIPT_DIR/suites"
TEST_EXECS_DIR="$SCRIPT_DIR/execs"

for dir in "$SUITES_DIR"/valid/*; do
    [ -d "$dir" ] || continue

    "$TEST_EXECS_DIR/tparser" "$dir"
done

$TEST_EXECS_DIR/tbase
$TEST_EXECS_DIR/tstring
$TEST_EXECS_DIR/tinteger
$TEST_EXECS_DIR/treal
$TEST_EXECS_DIR/tbool
$TEST_EXECS_DIR/tarray
$TEST_EXECS_DIR/tobject
