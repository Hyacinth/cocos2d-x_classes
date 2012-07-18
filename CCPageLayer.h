#ifndef CC_PAGELAYER_H
#define CC_PAGELAYER_H

#include <stdint.h>
#include "cocos2d.h"
#include "CCTouch+Position.h"
#include "CCNode+Position.h"

using namespace cocos2d;

namespace page_layer{
    typedef uint8_t PagesCount;



    class CCPageLayerDelegate
    {
    public:
    };



    class CCPageLayerDataSource
    {
    public:
        virtual PagesCount getPagesCount() = 0;
        virtual CCLayer *layerOfPageIndex(const PagesCount &c) = 0;
    };



    class CCPageLayer : public CCLayerColor
    {
    public:
        bool init(const float &width, const float &height);
        void onEnter();

        void setDataSource(CCPageLayerDataSource *data_source);
        void setDelegate(CCPageLayerDelegate *delegate);

        void registerWithTouchDispatcher();
        bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
        void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
        void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

    protected:

    private:
        bool isPageIndexLegal(const int16_t &index) const;
        float getPageX(const PagesCount &index) const;
        void addLayersOfEachPage();
        void addALayer(const PagesCount &index);
        void moveToPage(const PagesCount &index);

        CCSize size_;
        CCPageLayerDataSource *data_source_;
        CCPageLayerDelegate *delegate_;
        PagesCount cur_page_;
        float began_touch_x;
        float began_layer_x;
    };



    inline void CCPageLayer::setDataSource(CCPageLayerDataSource *data_source)
    {
        data_source_ = data_source;
    }


    inline void CCPageLayer::setDelegate(CCPageLayerDelegate *delegate)
    {
        delegate_ = delegate;
    }


    inline void CCPageLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
    {
        CCPoint now = getTouchPosition(*pTouch);
        setNodeLeft(this, began_layer_x + now.x - began_touch_x);
    }


    inline bool CCPageLayer::isPageIndexLegal(const int16_t &index) const
    {
        return 0 <= index && index < data_source_->getPagesCount();
    }


    inline float CCPageLayer::getPageX(const PagesCount &index) const
    {
        return size_.width * index;
    }
};

#endif
