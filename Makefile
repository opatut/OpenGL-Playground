default: bake run

bake:
	mkdir -p build
	cd build/ && cmake .. && make -j4

run:
	./GL
