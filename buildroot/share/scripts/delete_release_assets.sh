#!/bin/bash
#
# delete_release_assets.sh
#
# Usage: ./buildroot/share/scripts/delete_release_assets.sh [tag_name] e.g. v1.0.1
#
# Script to delete all assets from a specified GitHub release tag iteratively.
#

# --- Configuration ---
OWNER="classicrocker883" # e.g., "octocat"
REPO="MRiscoCProUI"		 # e.g., "my-project"
TAG_NAME="$1"			 # Pass the tag name as the first argument
# ---------------------

attout()  { echo -e "\033[0;30m$1\033[0m" ; }
errout()  { echo -e "\033[0;31m$1\033[0m" ; }
succout() { echo -e "\033[0;32m$1\033[0m" ; }
warnout() { echo -e "\033[0;33m$1\033[0m" ; }

# Check for required GitHub CLI and JQ tools
if ! command -v gh &> /dev/null; then
    errout "Error: GitHub CLI (gh) not found. Please install it."
    exit 1
fi
if ! command -v jq &> /dev/null; then
    errout "Error: jq not found. Please install it (e.g., sudo apt install jq)."
    exit 1
fi

# Ensure a tag name was provided
if [ -z "$TAG_NAME" ]; then
    warnout "Usage: $0 [tag_name]"
    exit 1
fi

echo "--- Starting iterative deletion of assets for tag: $TAG_NAME ---"

# 1. Fetch the list of asset names using GitHub CLI and jq
# We use gh api to hit the REST endpoint and jq to parse the asset names.
ASSETS_JSON=$(gh api "repos/$OWNER/$REPO/releases/tags/$TAG_NAME" --jq '.assets[].name' 2>/dev/null)

if [ $? -ne 0 ]; then
    errout "Error: Could not retrieve release information for tag $TAG_NAME"
	warnout "Check if the tag exists and your token/permissions are correct."
    exit 1
fi

if [ -z "$ASSETS_JSON" ]; then
    errout "No assets found for tag $TAG_NAME. Exiting."
    exit 0
fi

# 2. Iterate through each asset name and delete it
echo "$ASSETS_JSON" | while read -r ASSET_NAME; do
    attout "Attempting to delete asset: $ASSET_NAME"

    # gh release delete-asset performs the one-by-one deletion
    # --yes flag skips the confirmation prompt
    gh release delete-asset "$TAG_NAME" "$ASSET_NAME" --repo "$OWNER/$REPO" --yes

	if [ $? -ne 0 ]; then
        errout "❌ Failed to delete: $ASSET_NAME"
        # The loop will automatically continue to the next asset
    fi
done

succout "--- ✅ Asset deletion process complete! ---"

attout "Deleting release and tag $TAG_NAME automatically..."

gh release delete "$TAG_NAME" --repo "$OWNER/$REPO" --cleanup-tag --yes

if [ $? -eq 0 ]; then
    succout "🎉 Release and tag $TAG_NAME successfully deleted."
else
    errout "⚠️ Failed to delete release and tag $TAG_NAME. You may need to delete the tag manually."
    # The script will now exit, but the prior asset deletion was successful.
fi
