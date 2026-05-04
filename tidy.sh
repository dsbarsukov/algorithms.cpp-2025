#!/bin/bash

CHECKS='-*,clang-analyzer-*,performance-*,bugprone-*'
FILES=$(git ls-files '*.cpp' '*.cxx' '*.cc' | grep -v 'test' | tr '\n' ' ')

if [[ -z "$FILES" ]]; then
  echo "No source files to analyze."
  exit 0
fi

set -eo pipefail

for f in $FILES; do
  echo "Running clang-tidy on $f"
  clang-tidy -checks="$CHECKS" -system-headers=false "$f" --quiet -- -std=c++17 -I/usr/local/include 2>&1
done
