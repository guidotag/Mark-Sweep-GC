exp_name=gc_big
nosch=(010 025 050 075 100)

for p in {0..4}
do
	file_name=${exp_name}_${nosch[p]}
	
	epstopdf ${file_name}.eps
	cp ${file_name}.pdf ../informe/texplots
	cp ${file_name}.tex ../informe/texplots
	rm ${file_name}.eps
	rm ${file_name}.pdf
	rm ${file_name}.tex
done
