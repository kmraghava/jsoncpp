#!/bin/sh

SCRIPT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)

SUITES_DIR="$SCRIPT_DIR/suites"
TEST_EXEC="$SCRIPT_DIR/execs/tsuites"

for dir in "$SUITES_DIR"/valid/*; do
    [ -d "$dir" ] || continue

    "$TEST_EXEC" "$dir"
done

