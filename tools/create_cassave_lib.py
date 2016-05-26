import js2c
import sys
import os


def main():
    # the output file path
    cassave_dir = sys.argv[1]

    # list of module to include
    natives = [
        'io.js'
    ]

    # assert current dir is cassave lib dir and save current state
    with cwd_stack(os.path.join(cassave_dir, "lib")) as dir_stack:
        # output_dir = cassave_dir + build/cassave_lib.h
        output_dir = os.path.join(os.getcwd(), '../build/cassave_lib.h')

        # create the file
        js2c.JS2C(natives, [output_dir])

class cwd_stack:
    def __init__(self, dir):
        self.to_dir = dir
        self.from_dir = None

    def __enter__(self):
        self.from_dir = os.getcwd()
        os.chdir(self.to_dir)

    def __exit__(self, exc_type, exc_val, exc_tb):
        os.chdir(self.from_dir)


if __name__ == '__main__':
    main()
