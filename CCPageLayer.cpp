#include "CCPageLayer.h"
#include <cmath>

using namespace page_layer;

const float MOVE_SPEED = 1500;
const float CHNAGE_PAGE_DIS = 40;


bool CCPageLayer::init(const float &width,
                       const float &height)
{
    if (CCLayerColor::init()) {
        this->setOpacity(255);
        size_ = CCSizeMake(width, height);
        data_source_ = NULL;
        delegate_ = NULL;
        this->setIsTouchEnabled(true);

        return true;
    } else {
        return false;
    }
}


void CCPageLayer::onEnter()
{
    DASSERT(data_source_ != NULL);
    CCLayerColor::onEnter();

    PagesCount c = data_source_->getPagesCount();
    this->setContentSize(CCSizeMake(c * size_.width, size_.height));
    this->addLayersOfEachPage();
    cur_page_ = 0;
}


void CCPageLayer::registerWithTouchDispatcher()
{
//    DPRINT("CCPageLayer::registerWithTouchDispatcher called.");
    CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, false);
}


bool CCPageLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
//    DPRINT("ccTouchBegan called.");
    began_touch_x = getTouchPosition(*pTouch).x;
    began_layer_x = getNodeLeft(*this);
    return true;
}


void CCPageLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    float now_x = getNodeLeft(*this);
    int t = (began_layer_x - now_x) / CHNAGE_PAGE_DIS;
    int page_inc = t / fabs(t);
//    DPRINT("page_inc = %d", page_inc);
    int to_page = cur_page_ + page_inc;
//    DPRINT("to_page = %d", to_page);
//    DPRINT("cur_page_ = %d", cur_page_);
    
    if (this->isPageIndexLegal(to_page)) {
        this->moveToPage(to_page);
    } else {
        this->moveToPage(cur_page_);
    }
}


void CCPageLayer::addLayersOfEachPage()
{
    PagesCount pc = data_source_->getPagesCount();

    for (int i=0; i<pc; ++i) {
        this->addALayer(i);
    }
}


void CCPageLayer::addALayer(const PagesCount &index)
{
    CCLayer *layer = data_source_->layerOfPageIndex(index);
    float x = this->getPageX(index);
    layer->setPosition(CCPointMake(x, 0));
    this->addChild(layer);
}


void CCPageLayer::moveToPage(const PagesCount &index)
{
    DASSERT(this->isPageIndexLegal(index));
//    DPRINT("moveToPage called.");
//    DPRINT("index = %d", index);
    float x = this->getPageX(index);
    DPRINT("x = %f", x);
    CCPoint dst = CCPointMake(-x, getNodeBottom(*this));
    float dis = x + getNodeLeft(*this);
//    DPRINT("cur_x = %f", getNodeLeft(*this));
    float time = fabs(dis / MOVE_SPEED);
//    DPRINT("time = %f", time)
    CCMoveTo *move = CCMoveTo::actionWithDuration(time, dst);
    this->runAction(move);
    cur_page_ = index;
}
