#foreach mark-sweep function
#	foreach probability parameter pr
#		foreach number of objects
#			test

exp_name=gc_big
function=(std fast)
num_objects=(500 1000 1500 2000 2500 3000 3500 4000 4500 5000)
num_fields=(5 10 15 20 25 30 35 40 45 50)
pr_adj=(0.1 0.25 0.5 0.75 1)
pr_src=(0.01 0.01 0.01 0.01 0.01)

cd ..
cd ..
cd project
make clean
make

for f in {0..1}
do
	for p in {0..4}
	do
		output_file=${exp_name}_${function[f]}_${pr_adj[p]}_${pr_src[p]}.out
		for n in {0..9}
		do
			./bin/gc ${function[f]} -f $output_file -t ${num_objects[n]} ${num_fields[n]} ${pr_adj[p]} ${pr_src[p]}
		done
		cp output/$output_file ../experimentos/$exp_name
		rm output/$output_file
	done
done

