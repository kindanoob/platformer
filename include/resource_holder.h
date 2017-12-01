#ifndef RESOURCE_HOLDER_H_
#define RESOURCE_HOLDER_H_

#include "texture_manager.h"
#include "font_manager.h"

class Resource_holder {
public:
    Resource_holder();
    Texture_manager textures;
    Font_manager fonts;
private:
};

#endif // RESOURCE_HOLDER_H_
