#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include"curl/include/win32/curl/curl.h"
class GameGround : public cocos2d::Layer
{

private:

public:

	static cocos2d::Scene* createScene();
	static int who;
	cocos2d::Label *label;
	
	static std::map<std::string, std::string> dict;
	virtual bool init();
	virtual void onEnter();
	virtual void signin(std::string);
	void menuCloseCallback(cocos2d::Ref* pSender);
	void menuTufuCallback(cocos2d::Ref* pSender);
	void menuPeopleCallback(cocos2d::Ref* pSender);
	virtual void update(float dt);

	CREATE_FUNC(GameGround);
};