ls -R $1 > /tmp/ls-R
cat /tmp/ls-R | grep $2
# $1 - path
# $2 - pattern
