function=fast
num_objects=10
num_fields=2
pr_adj=0.15
pr_src=0.1
output_file=gc.out

make clean
make gc
#./bin/gc $function -f $output_file -t $num_objects $num_fields $pr_adj $pr_src
./bin/gc $function -v $num_objects $num_fields $pr_adj $pr_src
