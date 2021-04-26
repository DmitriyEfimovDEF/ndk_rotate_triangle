//
//  Triangle.hpp
//  cpp-triangle-test
//
//  Created by Stepan Kopylov on 15/04/2021.
//

#ifndef Triangle_hpp
#define Triangle_hpp

#include <stdio.h>
#include <functional>

#define NANOVG_GLES2_IMPLEMENTATION

#ifdef __APPLE__
#include "OpenGLES/ES2/glext.h"
#elif __ANDROID__

#include <GLES2/gl2.h>

#endif

#include "nanovg.h"

class Triangle {
    typedef std::function<void(float)> RadCallback;
public:
    void draw(float w, float h, float scale, float angle);

    void setRadCallback(RadCallback radCallback);

private:
    RadCallback radCallback = nullptr;
    bool nanovgInitialized = false;
    NVGcontext *vg;

    double degreesToRadians(double degree);

    void prepareToDraw();
};

#endif /* Triangle_hpp */
