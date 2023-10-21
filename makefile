all:main

main:led_dir.c
	g++ -o led_rand led_dir.c -std=c++20 -Wall -I /home/metoro/rpi-rgb-led-matrix/include -I /home/metoro/LED_Panel_All -L /home/metoro/rpi-rgb-led-matrix/lib -lrgbmatrix -I /home/metoro/stb -lwiringPi -g -O0

