#!/bin/bash

INPUT_FILE="Marlin/Configuration.h"
# INPUT_FILE="Marlin/Configuration_adv.h"
OUTPUT_FILE="configurations/_Define_Configuration.h"
# OUTPUT_FILE="configurations/_Define_Configuration_adv.h"

# Write header
# * Configuration_adv.h Defines

cat <<EOF > "$OUTPUT_FILE"
/**
 * Configuration.h Defines
 */
#pragma once

EOF

# Extract and clean defines, strip trailing spaces
grep "#define" "$INPUT_FILE" | \
    sed 's/.*#define/#define/' | \
    sed 's/\/\/.*//' | \
    awk '{ if (NF >= 2) print "// " $0 }' | \
    sed 's/[[:space:]]\+$//' \
    >> "$OUTPUT_FILE"
