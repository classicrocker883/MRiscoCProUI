#!/bin/bash
#
# apply_patch.sh
#
# Usage: ./buildroot/share/scripts/apply_patch.sh
# Run script in the root folder.
#
# Automatically generate patch files from uncommitted changes (pulled and ready to Merge)
# in 'Marlin/Configuration|_adv.h' and apply them to all files in 'configurations/'.
#

# --- Configuration ---
# Define colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
NC='\033[0m' # No Color

# The base directory where your target configuration files are located
BASE_DIR="configurations"

# Array of files to process.
# Format: "target_filename|marlin_path|strip_level"
FILE_DETAILS=(
    "Configuration.h|Marlin/Configuration.h|2"
    "Configuration-MP.h|Marlin/Configuration.h|2"
    "Configuration_adv.h|Marlin/Configuration_adv.h|2"
)

# --- Argument & System Validation ---

# Function to check for required commands
check_command() {
    if ! command -v "$1" &> /dev/null; then
        echo -e "${RED}❌ Error: '$1' command not found. Please install $1.${NC}"
        exit 1
    fi
}

# Function to display usage
usage() {
    echo -e "${GREEN}Usage: $0${NC}"
    echo "This script automatically generates patches from uncommitted changes in Marlin/ and applies them to all files in the '$BASE_DIR' directory tree."
    echo ""
    exit 0
}

# Check for help flag
if [[ "$1" == "-h" || "$1" == "--help" ]]; then
    usage
fi

# Check for required binaries
check_command "git"
check_command "patch"
check_command "find"
check_command "sed"

# Check if BASE_DIR exists
if [ ! -d "$BASE_DIR" ]; then
    echo -e "${RED}❌ Error: Base directory '$BASE_DIR' not found. Check your configuration.${NC}"
    exit 1
fi

# --- Script Logic ---

SCRIPT_DIR="$(pwd)"
echo "Patch files will be generated and saved in: $SCRIPT_DIR"

# 1. --- PATCH GENERATION PHASE ---
echo -e "\n${YELLOW}==========================================================${NC}"
echo -e "${YELLOW}PHASE 1: ⚙️ Generating Patch Files from Uncommitted Git Diff${NC}"
echo -e "${YELLOW}==========================================================${NC}"

declare -A GENERATED_PATCHES
FILE_DETAILS_UPDATED=()

for DETAIL in "${FILE_DETAILS[@]}"; do
    IFS='|' read -r TARGET_FILENAME MARLIN_PATH STRIP_LEVEL <<< "$DETAIL"

    PATCH_SOURCE_KEY="${MARLIN_PATH//\//_}"
    PATCH_FILE="${PATCH_SOURCE_KEY}.patch.tmp"

    if [[ -z "${GENERATED_PATCHES[$PATCH_SOURCE_KEY]}" ]]; then

        echo "Generating patch for $MARLIN_PATH -> $PATCH_FILE"

        if git diff HEAD "$MARLIN_PATH" > "$PATCH_FILE"; then

            if [ -s "$PATCH_FILE" ]; then
                echo -e "${GREEN}✅ Patch generated successfully.${NC}"
                GENERATED_PATCHES[$PATCH_SOURCE_KEY]="$PATCH_FILE"
            else
                echo -e "${YELLOW}⚠️ Warning: No uncommitted changes found in $MARLIN_PATH. Patch file is empty.${NC}"
                rm -f "$PATCH_FILE"
                GENERATED_PATCHES[$PATCH_SOURCE_KEY]=""
            fi
        else
            echo -e "${RED}❌ Error: Failed to generate git diff for $MARLIN_PATH. Check file path.${NC}"
            GENERATED_PATCHES[$PATCH_SOURCE_KEY]=""
        fi
    fi

    FINAL_PATCH_FILE="${GENERATED_PATCHES[$PATCH_SOURCE_KEY]}"
    FILE_DETAILS_UPDATED+=("$TARGET_FILENAME|$FINAL_PATCH_FILE|$STRIP_LEVEL|$MARLIN_PATH")

done

FILE_DETAILS=("${FILE_DETAILS_UPDATED[@]}")

# 2. --- PATCH APPLICATION PHASE ---
echo -e "\n${YELLOW}==========================================================${NC}"
echo -e "${YELLOW}PHASE 2: 🛠️ Applying Generated Patch Files in '$BASE_DIR'${NC}"
echo -e "${YELLOW}==========================================================${NC}"

for DETAIL in "${FILE_DETAILS[@]}"; do
    IFS='|' read -r TARGET_FILENAME PATCH_FILE STRIP_LEVEL MARLIN_PATH <<< "$DETAIL"

    if [ -z "$PATCH_FILE" ]; then
        echo "Skipping application for $TARGET_FILENAME (no patch generated)."
        continue
    fi

    FULL_PATCH_PATH="$SCRIPT_DIR/$PATCH_FILE"
    EXPECTED_PATCH_FILENAME=$(basename "$MARLIN_PATH")

    echo -e "\n--- Processing: ${YELLOW}$TARGET_FILENAME${NC} with patch $PATCH_FILE ---"

    find "$BASE_DIR" -type f -name "$TARGET_FILENAME" -print0 | while IFS= read -r -d $'\0' TARGET_FILE_PATH; do
        echo -e "  -> Applying patch to: ${TARGET_FILE_PATH}"

        TARGET_DIR=$(dirname "$TARGET_FILE_PATH")

        if ! pushd "$TARGET_DIR" > /dev/null; then
            echo -e "  ${RED}❌ Could not change directory to $TARGET_DIR. Skipping.${NC}"
            continue
        fi

        CURRENT_PATCH_PATH="$FULL_PATCH_PATH"
        TEMP_MODIFIED_PATCH=""

        # KEY FIX: Modify the patch file if TARGET_FILENAME doesn't match EXPECTED_PATCH_FILENAME
        if [[ "$TARGET_FILENAME" != "$EXPECTED_PATCH_FILENAME" ]]; then
            TEMP_MODIFIED_PATCH="$SCRIPT_DIR/${PATCH_FILE}.modified"

            # Use sed to replace all instances of the expected filename with the actual target filename
            # This is done on the diff header lines.
            sed "s|${EXPECTED_PATCH_FILENAME}|${TARGET_FILENAME}|g" "$FULL_PATCH_PATH" > "$TEMP_MODIFIED_PATCH"

            CURRENT_PATCH_PATH="$TEMP_MODIFIED_PATCH"
        fi

        # Apply the patch
        if patch -p"$STRIP_LEVEL" --silent --forward -N --no-backup-if-mismatch < "$CURRENT_PATCH_PATH"; then
            echo -e "  ${GREEN}✅ Success!${NC}"
        else
            echo -e "  ${RED}❌ Failure: Patch could not be applied. Checking verbose output...${NC}"
            # For debugging, run the command again without --silent
            patch -p"$STRIP_LEVEL" --forward -N < "$CURRENT_PATCH_PATH"
        fi

        # Clean up the temporary modified patch file if created
        if [ ! -z "$TEMP_MODIFIED_PATCH" ]; then
            rm -f "$TEMP_MODIFIED_PATCH"
        fi

        popd > /dev/null
    done
done

# 3. --- CLEANUP PHASE ---
echo -e "\n${YELLOW}==========================================================${NC}"
echo -e "${YELLOW}PHASE 3: 🧹 Cleaning Up Temporary Files and Stage Commits${NC}"
echo -e "${YELLOW}==========================================================${NC}"

# Clean up generated temporary patch files
for UNIQUE_PATCH_FILE in "${GENERATED_PATCHES[@]}"; do
    if [ ! -z "$UNIQUE_PATCH_FILE" ]; then
        rm -f "$UNIQUE_PATCH_FILE"
        echo -e "🗑️ Removed temporary patch file: ${UNIQUE_PATCH_FILE}"
    fi
done

# Clean up reject files
find "$BASE_DIR" -type f -name "*.rej" -delete
echo -e "🗑️ Removed all *.rej files from '$BASE_DIR'.${NC}"

# Stage changes
echo -e "\n${YELLOW}--- Staging Changes for Commit ---${NC}"
if git add "$BASE_DIR"; then
    echo -e "${GREEN}✅ Successfully staged all changes in '$BASE_DIR'.${NC}"
else
    echo -e "${RED}❌ Error staging changes in '$BASE_DIR'. Please check the git status manually.${NC}"
fi

# Finish
echo -e "\n--- ${GREEN}Script Finished${NC} ---"
