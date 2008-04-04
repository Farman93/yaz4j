#!/bin/sh
# $Id: tstmarcxml.sh,v 1.3 2006/08/28 12:34:42 adam Exp $
# Tests reading of MARCXML and checks that we get identical ISO2709 output.
#
# Reads marc?.xml files , Generates marc?.xml.marc files
srcdir=${srcdir:-.}
ecode=0
# Skip this test if Libxml2 support is not enabled
../util/yaz-marcdump -x >/dev/null 2>&1
if test $? = "3"; then
    exit 0
fi
for f in ${srcdir}/marc?.xml; do
    NEW=`basename ${f}`.new.marc
    OLD=${f}.marc
    DIFF=`basename ${f}`.diff
    ../util/yaz-marcdump -f utf-8 -t utf-8 -x -I $f > $NEW
    if test $? != "0"; then
	echo "Failed decode of $f"
	ecode=1
    elif test -f $OLD; then
        if diff $OLD $NEW >$DIFF; then
	    rm $DIFF
	    rm $NEW
	else
	    echo "$f: $NEW and $OLD Differ"
	    ecode=1
	fi
    else
	echo "$f: Making test result $OLD for the first time"
	mv $NEW $OLD
    fi
done
exit $ecode

# Local Variables:
# mode:shell-script
# sh-indentation: 2
# sh-basic-offset: 4
# End:
