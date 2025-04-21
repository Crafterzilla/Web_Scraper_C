#!/bin/bash

echo "Printing files"

for file in ./output/site_*_c*; do
    if [[ -f "$file" ]]; then
        echo "===== $file ====="
        cat "$file"
        echo                    # optional blank line between files
    else
        echo "No files matched."
    fi
done
