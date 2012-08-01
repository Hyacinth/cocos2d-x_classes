#ifndef ChemLLK_CCTouch_Position_h
#define ChemLLK_CCTouch_Position_h

#include "cocos2d.h"

using namespace cocos2d;

CCPoint getTouchPosition(const CCTouch &touch);
bool isTouchInNodeArea(const CCTouch *touch, const CCNode *node);

#endif
