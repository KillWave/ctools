#include <Cello/Cello.h>

//TODO
var import(var args) {
    // show($S("import"));
    foreach(arg in args) {
         return arg;
    }

   
}
var from(var args) {
    // show($S("from"));
     foreach(arg in args) {
        return arg;
    }
    
}

var number(var args){
    foreach(arg in args) {
        return $I(atoi(c_str(arg)));
    }
}
var string(var args){
    foreach(arg in args) {
        
        return arg;
    }
     
}

int main(int argc, char** argv) {
    var file = new(File, $S("test.txt"), $S("r"));
    var str = new(String, $S(""));
    var key = new(String, $S(""));
    var arrFn = new(Array, Function);
    var arrArgs = new(Array, String);
   
    var keyTable = new(Table, String, Function);
    set(keyTable, $S("import"), $(Function, import));
    set(keyTable, $S("from"), $(Function, from));
    set(keyTable, $S("number"), $(Function, number));
    set(keyTable, $S("string"), $(Function, from));

    bool isArgs = false;

    char c[2];
    c[1] = '\0';
    while (!seof(file)) {
        sread(file, c, 1);
        append(str, $S(c));
        try {
            push(arrFn, get(keyTable, str));
            resize(str, 0);
            resize(key, 0);
        }
        catch (e in KeyError) {
            if (eq($S(c), $S(" \0")) ||eq($S(c), $S("\n\0"))) {
                if (!empty(key)) {
                    push(arrArgs, key);
                    resize(str, 0);
                    resize(key, 0);
                }
                isArgs = !isArgs;
                continue;
            }
            if (isArgs) append(key, $S(c));
            continue;

        }
    }

    foreach(i in range($I(len(arrFn)))) {
        show(call(get(arrFn, i), get(arrArgs, i)));
    }
    return 1;
}
