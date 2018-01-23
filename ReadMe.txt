running each executable

for serial access
./file_name nodes(n) operations(m) M_member M_insert
ex: ./serial 1000 10000 0.3 0.6
	
Fraction for M_delete is calculated.

one mutex for entire list access
./file_name nodes(n) operations(m) M_member M_insert thread_amount
ex: ./one_mutex 1000 10000 0.3 0.6 1000
	
Fraction for M_delete is calculated.

read write lock
./file_name nodes(n) operations(m) M_member M_insert thread_amount
ex: ./read_write_lock 1000 10000 0.3 0.6 1000
	
Fraction for M_delete is calculated.



compiling source code
gcc -o file_name_to_create filename -lpthread
