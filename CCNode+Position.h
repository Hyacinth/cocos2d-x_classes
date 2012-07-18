#ifndef ChemLLK_CCNode_Location_h
#define ChemLLK_CCNode_Location_h

#include "cocos2d.h"

using namespace cocos2d;


void setNodeHeight(CCNode *pNode, const float &height);
void setNodeWidth(CCNode *pNode, const float &width);
void setNodeTop(CCNode *pNode, const float &top);
void setNodeBottom(CCNode *pNode, const float &bottom);
void setNodeLeft(CCNode *pNode, const float &left);
void setNodeRight(CCNode *pNode, const float &right);

float getNodeHeight(const CCNode &node);
float getNodeWidth(const CCNode &node);
float getNodeTop(const CCNode &node);
float getNodeBottom(const CCNode &node);
float getNodeLeft(const CCNode &node);
float getNodeRight(const CCNode &node);

CCRect getNodeRect(const CCNode &node);

inline void setNodeHeight(CCNode *pNode, const float &height)
{
    CCSize size = pNode->getContentSize();
    size.height = height;
    pNode->setContentSize(size);
}


inline void setNodeWidth(CCNode *pNode, const float &width)
{
    CCSize size = pNode->getContentSize();
    size.width = width;
    pNode->setContentSize(size);
}


inline void setNodeTop(CCNode *pNode, const float &top)
{
    CCPoint point = pNode->getPosition();
    point.y = top - getNodeHeight(*pNode);
    pNode->setPosition(point);
}


inline void setNodeBottom(CCNode *pNode, const float &bottom)
{
    CCPoint point = pNode->getPosition();
    point.y = bottom;
    pNode->setPosition(point);
}


inline void setNodeLeft(CCNode *pNode, const float &left)
{
    CCPoint point = pNode->getPosition();
    point.x = left;
    pNode->setPosition(point);
}


inline void setNodeRight(CCNode *pNode, const float &right)
{
    CCPoint point = pNode->getPosition();
    point.x = right - getNodeWidth(*pNode);
    pNode->setPosition(point);
}


inline float getNodeHeight(const CCNode &node)
{
    CCNode &ncNode = const_cast<CCNode &>(node);
    return ncNode.getContentSize().height;
}


inline float getNodeWidth(const CCNode &node)
{
    CCNode &ncNode = const_cast<CCNode &>(node);
    return ncNode.getContentSize().width;
}


inline float getNodeTop(const CCNode &node)
{
    return getNodeBottom(node) + getNodeHeight(node);
}


inline float getNodeBottom(const CCNode &node)
{
    CCNode &ncNode = const_cast<CCNode &>(node);
    return ncNode.getPosition().y;
}


inline float getNodeLeft(const CCNode &node)
{
    CCNode &ncNode = const_cast<CCNode &>(node);
    return ncNode.getPosition().x;
}


inline float getNodeRight(const CCNode &node)
{
    return getNodeLeft(node) + getNodeWidth(node);
}


inline CCRect getNodeRect(const CCNode &node)
{
    CCNode &ncNode = const_cast<CCNode &>(node);
    CCSize size = ncNode.getContentSize();
    CCPoint pos = ncNode.getPosition();
    return CCRectMake(pos.x, pos.y, size.width, size.height);
}

#endif
