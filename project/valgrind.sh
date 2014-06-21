#Valgrind test script

VALGRIND=valgrind
BIN=./bin/tests
OKVALGRIND=0
make clean
make all
$VALGRIND --show-reachable=yes --leak-check=yes --error-exitcode=1 --suppressions=gc.supp -q $BIN
if [ $? != "0" ]; then
	OKVALGRIND=1
fi

if [ $OKVALGRIND == "0" ]; then
	echo "Valgrind... :)"
else
	echo "Valgrind... :("
fi
