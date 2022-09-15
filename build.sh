rm -r test_main core*
gcc test_main.c librelic_s.a libgmp.a -I ./include/ -I ./include/low -L /usr/local/lib -gdwarf-2 -p -O3 -g3 -o test_main_v3
