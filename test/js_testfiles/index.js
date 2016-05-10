"use strict";

class SayHello {
    constructor(name) {
        this.name = name;
    }

    say_hello() {
        printf("Hello, %!\n", this.name);
    }
}

new SayHello("Christian").say_hello();
