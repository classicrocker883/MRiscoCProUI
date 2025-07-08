#!/bin/bash

INPUT_FILE="Marlin/Configuration.h"
# INPUT_FILE="Marlin/Configuration_adv.h"
OUTPUT_FILE="_Undef_Configuration.h"
# OUTPUT_FILE="_Undef_Configuration_adv.h"

# Write header
# * Configuration_adv.h Undefines

cat <<EOF > "$OUTPUT_FILE"
/**
 * Configuration.h Undefines
 */
#pragma once

EOF

# Extract only the macro name
grep "#define" "$INPUT_FILE" | \
    sed 's/.*#define/#define/' | \
    sed 's/\/\/.*//' | \
    awk '{ if (NF >= 2) print "// #undef " $2 }' \
    >> "$OUTPUT_FILE"
