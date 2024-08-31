#!/bin/bash

DEFAULT_FILES=(resources/*)

if [ "$#" -eq 0 ]; then
    FILES=("${DEFAULT_FILES[@]}")
else
    FILES=("$@")
fi

run_checks() {
    local files=("$@")
    
    echo "Running BLAKE2s checks..."
    ./verifiers/checker_blake2s.sh "${files[@]}"
    
    echo "Running MD5 checks..."
    ./verifiers/checker_md5.sh "${files[@]}"
    
    echo "Running SHA256 checks..."
    ./verifiers/checker_sha256.sh "${files[@]}"
    
    echo "Running WHIRLPOOL checks..."
    ./verifiers/checker_whirlpool.sh "${files[@]}"
}

run_checks "${FILES[@]}"
