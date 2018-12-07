top_down: reg_alloc.c  list.c
	gcc reg_alloc.c list.c -o btm_up

clean: 
	rm -rf  btm_up btm_up_reg_alloc_report.txt

