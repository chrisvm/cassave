io = process.binding("io");

// test process.binding
function test_process_binding() {
    io.print(process.binding);

    // call with no params
    io.print("\nprocess() - no params");
    io.print(process.binding());

    // call with io param
    io.print("\nprocess(\"io\") call");
    io.print(process.binding("io"));

    // call with natives param
    io.print("\nprocess(\"natives\") call");
    io.print(process.binding("natives"));
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