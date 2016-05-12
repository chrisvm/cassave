var io = {}, io_bindings;

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

io_bindings = process.bindings('io');
module.exports = io;
