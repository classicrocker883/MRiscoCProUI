#!/bin/bash
#
# simulator_error.sh [linux|windows]
#
# Run if you encounter an error in the building MarlinSimulator.
# Errors may be different for using a probe/auto bed leveling and manual mesh.
#

# Define file paths
FILE1="Marlin/src/lcd/e3v2/proui/dwin_defines.h"
FILE2="Marlin/src/inc/Conditionals-5-post.h"
FILE3="ini/native.ini"
FILE4="Marlin/Configuration.h"
FILE5="platformio.ini"

# Define patterns to search for (from strings)
PATTERN1='#define INVERT_E0_DIR HMI_data.Invert_E0'
PATTERN2='#undef Z_MIN_ENDSTOP_HIT_STATE'
PATTERN3='release_flags.*-flto'
PATTERN4_BOARD='#define MOTHERBOARD'
PATTERN4_ENDSTOP='#define ENDSTOP_INTERRUPTS_FEATURE'
PATTERN4_PROUI='#define PROUI_EX 1'

# Check for command line argument for platform
PLATFORM_ENV=""
if [ "$1" == "windows" ]; then
    PLATFORM_ENV='simulator_windows'
elif [ "$1" == "linux" ]; then
    PLATFORM_ENV='simulator_linux_release'
fi

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
        sed -i "s|$PATTERN2|//#undef Z_MIN_ENDSTOP_HIT_STATE|" "$FILE2"
        echo "Updated $FILE2: Replaced '$PATTERN2'"
    else
        echo "Warning: Line '$PATTERN2' not found in $FILE2. No change made."
    fi
else
    echo "Error: $FILE2 not found. Skipping changes for this file."
fi

# --- Change 3: ini/native.ini ---
if [ -f "$FILE3" ]; then
    if grep -qE "$PATTERN3" "$FILE3"; then
        sed -i "/release_flags/ s/-flto/-fno-lto/" "$FILE3"
        echo "Updated $FILE3: Changed '-flto' to '-fno-lto' on a line containing 'release_flags'."
    else
        echo "Warning: Line containing 'release_flags' and '-flto' not found in $FILE3. No change made."
    fi
else
    echo "Error: $FILE3 not found. Skipping changes for this file."
fi

# --- Change 4: Marlin/Configuration.h ---
if [ -f "$FILE4" ]; then
    # Change MOTHERBOARD
    if grep -qE "$PATTERN4_BOARD" "$FILE4"; then
        sed -i "s|$PATTERN4_BOARD.*$|$PATTERN4_BOARD BOARD_SIMULATED|" "$FILE4"
        echo "Updated $FILE4: Added 'BOARD_SIMULATED' to '#define MOTHERBOARD'."
    else
        echo "Warning: Line containing '$PATTERN4_BOARD' not found in $FILE4. No change made."
    fi

    # Comment out ENDSTOP_INTERRUPTS_FEATURE
    if grep -qF "$PATTERN4_ENDSTOP" "$FILE4"; then
        sed -i "s|$PATTERN4_ENDSTOP|//$PATTERN4_ENDSTOP|" "$FILE4"
        echo "Updated $FILE4: Commented out '$PATTERN4_ENDSTOP'."
    else
        echo "Warning: Line '$PATTERN4_ENDSTOP' not found in $FILE4. No change made."
    fi

    # Comment out PROUI_EX 1
    if grep -qF "$PATTERN4_PROUI" "$FILE4"; then
        sed -i "s|$PATTERN4_PROUI|//$PATTERN4_PROUI|" "$FILE4"
        echo "Updated $FILE4: Commented out '$PATTERN4_PROUI'."
    else
        echo "Warning: Line '$PATTERN4_PROUI' not found in $FILE4. No change made."
    fi
else
    echo "Error: $FILE4 not found. Skipping changes for this file."
fi

# --- Change 5: platformio.ini ---
if [ -f "$FILE5" ] && [ ! -z "$PLATFORM_ENV" ]; then
    if grep -qE '^default_envs' "$FILE5"; then
        sed -i "s|^default_envs.*$|default_envs = $PLATFORM_ENV|" "$FILE5"
        echo "Updated $FILE5: Set 'default_envs' to '$PLATFORM_ENV'."
    else
        echo "Warning: Line containing 'default_envs' not found in $FILE5. No change made."
    fi
else
    echo "Error: $FILE5 not found or no platform specified. Skipping changes for this file."
fi

echo -e "\nScript complete."
