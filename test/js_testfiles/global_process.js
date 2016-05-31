// test process.binding
function test_process_binding() {
    print(process.binding);

    // call with no params
    print("\nprocess() - no params");
    print(process.binding());

    // call with io param
    print("\nprocess(\"io\") call");
    print(process.binding("io"));

    // call with natives param
    print("\nprocess(\"natives\") call");
    print(process.binding("natives"));
}

function print_header(text) {
    var side_count = 15, header = '';

    for (var x = 0; x < side_count; x += 1) {
        header += '*';
    }

    header += ' ' + text + ' ' + header;

    print(header);
}

(function () {
    print_header("Testing Binding function");
    test_process_binding();
})();