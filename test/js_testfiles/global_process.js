io = process.binding("io");

// test process.binding
function test_process_binding() {
    io.print(process.binding);

    // call with no params
    print_header("process() - no params");
    io.print(process.binding());

    // call with io param
    print_header("process(\"io\") call");
    io.print(process.binding("io"));

    // call with natives param
    print_header("process(\"natives\") call");
    var natives = process.binding("natives");
    io.print("natives: " + natives);

    // view all natives values
    print_header("natives.values");
    for (var nat in natives) {
        io.print("natives." + nat);
        io.print(natives[nat]);
    }
}

function print_header(text) {
    var side_count = 15, header = '';

    for (var x = 0; x < side_count; x += 1) {
        header += '*';
    }

    header += ' ' + text + ' ' + header;

    io.print(header);
}

(function () {
    print_header("Testing Binding function");
    test_process_binding();
})();