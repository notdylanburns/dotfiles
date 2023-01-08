#!/bin/bash

# Set default result directory to $HOME
resultdir="$1"
if [[ -z "$resultdir" ]] ; then
    resultdir="$HOME"
fi

# Get name of this file and containing directory
execfile=$(realpath $0)
filename=$(basename $execfile)
dir=$(dirname $execfile)

# Build binaries in .tools directory
make -C "${dir}/.tools"

# Files to ignore when installing
exclude=('.' '..' '.git' 'README.md')

# Build grep expression to exclude files in $exclude
grep_expr="(^${filename}$)"

for f in "${exclude[@]}" ; do
    grep_expr="${grep_expr}|(^${f}$)"
done

grep_expr=$(echo "$grep_expr" | sed -e 's/\./\\./g')


# Copy all files not in $exclude into result directory
for f in $(ls -a | grep -Pv $grep_expr) ; do
    echo cp -r "${dir}/${f}" "$resultdir"
    cp -r "${dir}/${f}" "$resultdir"
done