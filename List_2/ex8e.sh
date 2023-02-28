for i in man{1..8}
do
    echo "Man Chapter no $i:"
    find /usr/share/man/pl/$i -printf "%f\n" 2>/dev/null | cut -d. -f1
    echo "----"
done

# 2>/dev/null - get rid of an error message
# -printf "%f\n" - just file names, no path