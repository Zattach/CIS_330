gcc -std=c99 -c first.c
diff -y -B -b first.output first.master
numdiffs=`diff  -B -b first.output first.master | wc -l`
gcc -std=c99 -c avg.c
./avg
./avg
diff -y -B -b avg.output avg.master
numdiffs=`diff  -B -b avg.output avg.master | wc -l`
gcc -std=c99 -c rps.c
./rps
