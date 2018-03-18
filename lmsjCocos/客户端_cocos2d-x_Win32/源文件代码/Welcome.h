#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
class Welcome : public cocos2d::Layer
{
private:
public:
	static int loginflag;
	static cocos2d::Scene* createScene();
	cocos2d::Label *label;
	cocos2d::Sprite *conLabel;
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);
	void menuStartVisi(cocos2d::Ref* pSender);
	void menuStartVip(cocos2d::Ref* pSender);
	virtual void update(float dt);
	CREATE_FUNC(Welcome);
};

