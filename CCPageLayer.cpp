#include "CCPageLayer.h"
#include <cmath>

const float MOVE_SPEED = 1500;
const float CHNAGE_PAGE_DIS = 40;

CCPageLayer* CCPageLayer::node(const float &width, const float &height)
{
    CCPageLayer *layer = new CCPageLayer;
    if (layer->init(width, height)) {
        layer->autorelease();
        return layer;
    } else {
        return NULL;
    }
}


bool CCPageLayer::init(const float &width,
                       const float &height)
{
    if (CCLayer::init()) {
        size_ = CCSizeMake(width, height);
        data_source_ = NULL;
        delegate_ = NULL;
        this->setTouchEnabled(true);
        is_scrolling_ = false;

        return true;
    } else {
        return false;
    }
}


void CCPageLayer::onEnter()
{
    DASSERT(data_source_ != NULL);
    CCLayer::onEnter();

    size_t c = data_source_->getPagesCount(this);
    this->setContentSize(CCSizeMake(c * size_.width, size_.height));
    this->addLayersOfEachPage();
    cur_page_ = 0;
}


void CCPageLayer::onExit()
{
    CCLayer::onExit();

    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}


void CCPageLayer::registerWithTouchDispatcher()
{
    DPRINT("CCPageLayer::registerWithTouchDispatcher called.");
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(
            this,
            INT_MIN + 1,
            false);
}


bool CCPageLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    DPRINT("ccTouchBegan called.");
    if (isTouchInNodeArea(pTouch, this)) {
        began_touch_x_ = getTouchPosition(*pTouch).x;
        began_layer_x_ = getNodeLeft(*this);
        return true;
    } else {
        return false;
    }
}


void CCPageLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint now = getTouchPosition(*pTouch);
    setNodeLeft(this, began_layer_x_ + now.x - began_touch_x_);

    if (!is_scrolling_) {
        if (delegate_ != NULL) {
            delegate_->onPageLayerStartToScroll(this);
        }

        is_scrolling_ = true;
    }
}


void CCPageLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    DPRINT("ccTouchEnded called.");
    float now_x = getNodeLeft(*this);
    int t = (began_layer_x_ - now_x) / CHNAGE_PAGE_DIS;
//    DPRINT("t = %d", t);
    int page_inc = (t == 0) ? 0 : t / fabs(t);
//    DPRINT("page_inc = %d", page_inc);
    int to_page = cur_page_ + page_inc;
//    DPRINT("cur_page_ = %d", cur_page_);
//    DPRINT("to_page = %d", to_page);

    if (this->isPageIndexLegal(to_page)) {
//        DPRINT("move to to_page.");
        this->moveToPage(to_page);
    } else {
//        DPRINT("move to cur_page.");
        this->moveToPage(cur_page_);
    }
}


void CCPageLayer::addLayersOfEachPage()
{
    size_t pc = data_source_->getPagesCount(this);

    for (int i=0; i<pc; ++i) {
        this->addALayer(i);
    }
}


void CCPageLayer::addALayer(const size_t &index)
{
    CCLayer *layer = data_source_->layerOfPageIndex(this, index);
    float x = this->getPageX(index);
    setNodeLeft(layer, x + getNodeLeft(*layer));
    this->addChild(layer);
}


void CCPageLayer::moveToPage(const size_t &index)
{
    DASSERT(this->isPageIndexLegal(index));
    float x = this->getPageX(index);
    DPRINT("x = %f", x);
    CCPoint dst = CCPointMake(-x, getNodeBottom(*this));
    float dis = x + getNodeLeft(*this);
    float time = fabs(dis / MOVE_SPEED);
    CCMoveTo *move = CCMoveTo::create(time, dst);
    this->runAction(move);
    cur_page_ = index;
    this->addTimer(time);
}


void CCPageLayer::addTimer(const float &delay)
{
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(
            schedule_selector(CCPageLayer::onMoveEnded),
            this,
            0,
            false,
            0,
            delay);
}


void CCPageLayer::onMoveEnded(float delay)
{
    is_scrolling_ = false;
}
