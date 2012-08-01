#include "CCTouch+Position.h"
#include "position.h"
#include "CCNode+Position.h"


CCPoint getTouchPosition(const CCTouch &touch)
{
    CCTouch &ncTouch = const_cast<CCTouch &>(touch);
    CCPoint loc = ncTouch.locationInView();
    CCPoint result;
    result.x = loc.x;
    result.y = APP_SCREEN_HEIGHT - loc.y;
    return result;
}


bool isTouchInNodeArea(const CCTouch *touch, const CCNode *node)
{
#ifdef _QSW_TEST
    CCPoint touch_point = getTouchPosition(*touch);
    CCRect node_rect = getNodeRect(*node);
    DPRINT("touch pos: x = %f, y = %f", touch_point.x, touch_point.y);
    DPRINT("node rect = x = %f, y = %f, wid = %f, height = %f", 
           node_rect.origin.x,
           node_rect.origin.y,
           node_rect.size.width,
           node_rect.size.height);
#endif
    return IsPointInRect(getTouchPosition(*touch), getNodeRect(*node));
}
