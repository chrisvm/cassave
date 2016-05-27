"use strict";
print(process);

class SayHello {
    constructor(name) {
        this.name = name;
    }

    say_hello() {
        writef("Hello, %!\n", this.name);
    }
}

new SayHello("Christian").say_hello();
