Building the source
===================

To build, first enter the build dir

	cd build

then produce the makefiles with cmake

	cmake ..

After the files are created, make the native_test solution

	make native_test

This will produce the binary and copy the snapshots to the build dir
