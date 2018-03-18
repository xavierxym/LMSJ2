#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
class LoginVip : public cocos2d::Layer
{

private:

public:
	cocos2d::TextFieldTTF  *inputname;
		cocos2d::TextFieldTTF * inputpassw;
	static cocos2d::Scene* createScene();
	cocos2d::Label *label;

	static std::map<std::string, std::string> dict;
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);
	void menucCallback(cocos2d::Ref* pSender);
	virtual void update(float dt);
	virtual void signin(std::string , std::string );
	CREATE_FUNC(LoginVip);
};

