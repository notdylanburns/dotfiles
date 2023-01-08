resultdir="$1"
if [[ -z "$resultdir" ]] ; then
    resultdir="$HOME"
fi

execfile=$(realpath $0)
filename=$(basename $execfile)
dir=$(dirname $execfile)

exclude=('.' '..' '.git')

grep_expr="(^${filename}$)"

for f in "${exclude[@]}" ; do
    grep_expr="${grep_expr}|(^${f}$)"
done

grep_expr=$(echo "$grep_expr" | sed -e 's/\./\\./g')

for f in $(ls -a | grep -Pv $grep_expr) ; do
    echo cp -r "$dir/$f" "$resultdir"
    cp -r "$dir/$f" "$resultdir"
done