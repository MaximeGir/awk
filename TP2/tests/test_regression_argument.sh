#
# exec ./tests/test_regression_argument.sh &> test_regression_log
#

echo -e "1: test 1 argument (-H et -V) seul"
./filtre -H
./filtre -V

echo -e "2: test -H et -V sans arguments à l'option"
./filtre -H -V

echo -e "3: test -H et -H sans argument à l'option"
./filtre -H -H

echo -e "4: test -V et -V sans argument à l'option"
./filtre -V -V

echo -e "5: test -V et -H en ordre different sans argument à l'option"
./filtre -V -H

echo -e "6: test -V 1 argument"
./filtre -V test

echo -e "7: test -V 2 arguments"
./filtre -H test test2

echo -e "8: test -H 1 argument"
./filtre -H test

echo -e "9: test -H 2 arguments"
./filtre -H test test2

echo -e "10: test -H 1 argument et option -L sans arguments"
./filtre -H test -L

echo -e "11: test -H 1 argument et option -C sans arguments"
./filtre -H test -C

echo -e "12: test -H 2 arguments et option -L sans arguments"
./filtre -H test test2 -L

echo -e "13: test -H 2 arguments et option -C sans arguments"
./filtre -H test test2 -C

echo -e "14: test -V 1 argument et option -L sans arguments"
./filtre -V test -L

echo -e "15: test -V 1 argument et option -C sans arguments"
./filtre -V test -C

echo -e "16: test -V 2 arguments et option -L sans arguments"
./filtre -V test test2 -L

echo -e "17: test -V 2 arguments et option -C sans arguments"
./filtre -V test test2 -C 

echo -e "18: test -V 2 arguments et option -C avec 1 argument"
./filtre -V test test2 -C 1-2

echo -e "19: test -V 2 arguments et option -L avec 1 argument"
./filtre -V test test1 -L 1-2

echo -e "20: test -H 2 arguments et option -L avec 1 argument"
./filtre -H test test2 -L 0

echo -e "21: test -H 2 arguments et option -C avec 1 argument"
./filtre -H test test2 -C 1-2

echo -e "18: test -V 2 arguments et option -C avec 2 argument"
./filtre -V test test2 -C 2-1 0

echo -e "19: test -V 2 arguments et option -L avec 2 argument"
./filtre -V test test2 -L 2-1 0

echo -e "20: test -H 2 arguments et option -L avec 2 argument"
./filtre -H test test2 -L 2-1 0

echo -e "21: test -H 2 arguments et option -C avec 2 argument"
./filtre -H test test2 -C 0 9

echo -e "22: test -H 2 arguments et option -L avec 1 argument, option -C avec 1 argument"
./filtre -H test test2 -L 2-1 -C 0

echo -e "23: test -H 2 arguments et option -C avec 2 argument , option -L 1 argument"
./filtre -H test test2 -C 0 9 -L 9

echo -e "24: test -H 2 arguments et option -L avec 2 argument & -C 2 arguments"
./filtre -H test test2 -L 2-1 0 -C 2-1 2

echo -e "25: test -H 2 arguments et option -C avec 2 argument & -L 2 argument"
./filtre -H test test2 -C 0 9 -L 2 4


