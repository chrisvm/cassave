Dependencies
============


### V8

Cassave uses V8 for scripting and the base engine classes are implemented
in Javascript.

#### Building V8

To build, go to the official [V8 docs](https://github.com/v8/v8/wiki/Checking%20out%20source) to
checkout and build the lib.

##### depot_tools

First, depot tools is needed. If not installed, clone the repo
into a place where it can stay:

    # create depot tools dir
    mkdir ~/.depot_tools

    # change to that dir
    cd ~/.depot_tools

    # clone the repo
    git clone https://chromium.googlesource.com/chromium/tools/depot_tools.git

After that, all that is needed is to export to path the location of that dir. This line added to the
.bashrc file (or similar) is generally sufficient:

    # export to PATH var
    echo 'export PATH=~/depot_tools/depot_tools:"$PATH"' >> ~/.bash_profile


##### v8 source

After depot_tools are installed, change into cassave/deps dir and fetch de repo

    # cd in to deps
    cd ~/path/to/cassave/deps

    # get the source with depot_tools
    fetch v8

    # cd into v8 dir
    cd v8

    # sync all depends
    gclient sync

    # build v8 files (parameter for 2 cores pc's, adjust to your specs)
    make x64.release -j 2

