var io = {}, io_bindings = process.binding("io");

// io.write()
io.write = function () {
    return io_bindings.write.apply(io, arguments);
};

// io.print
io.print = function () {
    return io_bindings.print.apply(io, arguments);
};

// io.writef()
io.writef = function () {
    return io_bindings.writef.apply(io, arguments);
};

module.exports = io;
