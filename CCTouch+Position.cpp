#include "CCTouch+Position.h"
#include "position.h"


CCPoint getTouchPosition(const CCTouch &touch)
{
    CCTouch &ncTouch = const_cast<CCTouch &>(touch);
    return getCocos2dPosition(ncTouch.locationInView(ncTouch.view()));
}