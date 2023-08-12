#!/bin/bash
set -e

# Get the directory of the script
script_dir="$(dirname "$(realpath "$0")")"

# Navigate to the script directory
cd "$script_dir"

# Output the header comment and author information to the AUTHOR file
cat << EOH > AUTHORS
# This file lists all individuals having contributed content to the repository.
# For how it is generated, see 'generating_author.sh'.

$(git log --format='%aN <%aE>' | LC_ALL=C.UTF-8 sort -uf)
EOH
