#ifndef CC_PAGELAYER_H
#define CC_PAGELAYER_H

#include <stdint.h>
#include "cocos2d.h"
#include "CCTouch+Position.h"
#include "CCNode+Position.h"

using namespace cocos2d;

class CCPageLayer;



class CCPageLayerDelegate
{
public:
    virtual void onPageLayerStartToScroll(CCPageLayer *pageLayer) {}
};



class CCPageLayerDataSource
{
public:
    virtual size_t getPagesCount(CCPageLayer *pageLayer) = 0;
    virtual CCLayer *layerOfPageIndex(CCPageLayer *pageLayer,
                                      const size_t &index) = 0;
};



class CCPageLayer : public CCLayer
{
public:
    static CCPageLayer* node(const float &width, const float &height);

    bool init(const float &width, const float &height);
    void onEnter();
    void onExit();

    bool isScrolling() const;

    void setDataSource(CCPageLayerDataSource *data_source);
    void setDelegate(CCPageLayerDelegate *delegate);
    float getPageWidth() const;

    void registerWithTouchDispatcher();
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

protected:

private:
    bool isPageIndexLegal(const int16_t &index) const;
    float getPageX(const size_t &index) const;
    void addLayersOfEachPage();
    void addALayer(const size_t &index);
    void moveToPage(const size_t &index);

    void addTimer(const float &delay);

    void onMoveEnded(float delay);

    CCSize size_;
    CCPageLayerDataSource *data_source_;
    CCPageLayerDelegate *delegate_;
    size_t cur_page_;
    float began_touch_x_;
    float began_layer_x_;
    bool is_scrolling_;
};



inline bool CCPageLayer::isScrolling() const
{
    return is_scrolling_;
}


inline void CCPageLayer::setDataSource(CCPageLayerDataSource *data_source)
{
    data_source_ = data_source;
}


inline void CCPageLayer::setDelegate(CCPageLayerDelegate *delegate)
{
    delegate_ = delegate;
}


inline float CCPageLayer::getPageWidth() const
{
    return size_.width;
}


inline bool CCPageLayer::isPageIndexLegal(const int16_t &index) const
{
    CCPageLayer *nt = const_cast<CCPageLayer *>(this);
    return 0 <= index && index < data_source_->getPagesCount(nt);
}


inline float CCPageLayer::getPageX(const size_t &index) const
{
    return size_.width * index;
}


#endif
