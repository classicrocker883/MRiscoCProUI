#!/bin/bash
#
# simulator_error.sh
#
# Run if you encounter an error in the building MarlinSimulator.
# Errors may be different for using a probe/auto bed leveling and manual mesh.
#

# Define file paths
FILE1="Marlin/src/lcd/e3v2/proui/dwin_defines.h"
FILE2="Marlin/src/inc/Conditionals-5-post.h"
FILE3="ini/native.ini"

# Define patterns to search for (from strings)
PATTERN1='#define INVERT_E0_DIR HMI_data.Invert_E0'
PATTERN2='#undef Z_MIN_ENDSTOP_HIT_STATE'
GENERIC_PATTERN3='release_flags.*-flto' # Matches lines with 'release_flags' then anything, then '-flto'

echo "Starting script..."

# --- Change 1: Marlin/src/lcd/e3v2/proui/dwin_defines.h ---
if [ -f "$FILE1" ]; then
    if grep -qF "$PATTERN1" "$FILE1"; then
        sed -i "s|$PATTERN1|#define INVERT_E0_DIR false|" "$FILE1"
        echo "Updated $FILE1: Replaced '$PATTERN1'"
    else
        echo "Warning: Line '$PATTERN1' not found in $FILE1. No change made."
    fi
else
    echo "Error: $FILE1 not found. Skipping changes for this file."
fi

# --- Change 2: Marlin/src/inc/Conditionals-5-post.h ---
if [ -f "$FILE2" ]; then
    if grep -qF "$PATTERN2" "$FILE2"; then
        sed -i "s|^.*$PATTERN2|  //#undef Z_MIN_ENDSTOP_HIT_STATE|" "$FILE2"
        echo "Updated $FILE2: Replaced '$PATTERN2'"
    else
        echo "Warning: Line '$PATTERN2' not found in $FILE2. No change made."
    fi
else
    echo "Error: $FILE2 not found. Skipping changes for this file."
fi

# --- Change 3: ini/native.ini (using the more generic approach) ---
if [ -f "$FILE3" ]; then
    if grep -qE "$GENERIC_PATTERN3" "$FILE3"; then
        sed -i "/release_flags/ s/-flto/-fno-lto/" "$FILE3"
        echo "Updated $FILE3: Changed '-flto' to '-fno-lto' on a line containing 'release_flags'."
    else
        echo "Warning: Line containing 'release_flags' and '-flto' not found in $FILE3. No change made."
    fi
else
    echo "Error: $FILE3 not found. Skipping changes for this file."
fi

echo -e "\nScript complete."
