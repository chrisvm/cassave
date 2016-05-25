//
// Created by chrisvm on 05-25-16.
//

#ifndef CASSAVE_JS_NATIVEBINDING_H
#define CASSAVE_JS_NATIVEBINDING_H


class NativeBinding {
public:
    virtual char* getName()=0;
    static virtual void* getInstance()=0;
};


#endif //CASSAVE_JS_NATIVEBINDING_H
