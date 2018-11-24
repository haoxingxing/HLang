#pragma once
#include <QMap>
#include <QObject>
#include <QDebug>
#include <QStringList>
#include <functional>
#include <QWidget>
#include <QVector>
#define Has_Commandline_Front
#define needQWeight "Only Accept QGuiClass"
#define WhyBuiltinNewFailed "Class Not Find"
#define	WhyBuiltinMsgFailed "Class not Support"
#define WhyFunctionLoadFileFailed "File not find or can't read"
#define WhyIfExecFailed "Which or True or False Result not setup"
#define WhyHWindowAddWeightFailed needQWeight
#define WhyTcpSocketConnectWarring "[Warring]ConnectedSlotNotHandled"
#define WhyTcpSocketConnectSlotError "SIGNAL NOT FIND"
#define HClassMap QMap<QString, HObject*>
#define HArgs QVector<HObject*>
#define H_OBJECT(_name) \
private: \
QMap<QString,HObject*(_name::*)(HArgs args)> memberfuncs; \
public: HObject* exec(QString __name,HArgs args) { \
if (memberfuncs.contains(__name))\
return (this->*memberfuncs[__name])(args); \
return new HRet(nullptr, false, "[Class."#_name"][Function."+__name+"]Not Find"); \
}
#define DefineMemberFunction(__name,__function_address) memberfuncs.insert(__name,__function_address)
#define IsGuiClass 	this->QGuiClassHandle = (QWidget*)this;
#define CheckArgs(__needvalues) 	if (args.size() < __needvalues) return new HRet(nullptr,false,"Args too few or much:[Yours."+QString::number(args.size())+"][need."#__needvalues+"]");
#define CheckArgsType(__which,__kind) if (HObjectHelper(args[__which]).to<__kind>()==nullptr)return new HRet(nullptr,false,"ArgsType Incorrect [Arg."#__which"][TargetType.:"#__kind"]")
class HObject
{
public:
	HObject() {};
	virtual ~HObject() {};
	virtual HObject* exec(QString __name, HArgs args) {
		qDebug() << "Warring: HObject exec called[N." + __name + "]" << "[A." << args << "]";
		return new HObject;
	};
	QWidget* QGuiClassHandle = nullptr;
};

struct HCommand {
	QString *_class = nullptr;
	QString *_func = nullptr;
	QString *_self = nullptr;
	QStringList *_args = nullptr;
	QString *_backvalue_name = nullptr;
};
class HObjectHelper {
public:
	HObjectHelper(HObject* obj)
	{
		this->obj = obj;
	}
	template<typename _Target>
	_Target* to()
	{
		return dynamic_cast<_Target*>(obj);
	}
	operator QString () {
		return (dynamic_cast<HString*>(obj) == nullptr) ? QString("") : dynamic_cast<HString*>(obj)->toQString();
	}
	operator int() {
		return (dynamic_cast<HInt*>(obj) == nullptr) ? int(0) : *dynamic_cast<HInt*>(obj)->value();
	}
	operator bool()
	{
		return (dynamic_cast<HBool*>(obj) == nullptr) ? false : dynamic_cast<HBool*>(obj)->value();
	}
private:
	HObject* obj;
};
class HRet :public HObject
{
public:
	HRet(HObject* ret = nullptr, bool isSuccess = true, QString reason = "")
	{
		this->isSuccess = isSuccess;
		this->ret = ret;
		this->reason = reason;
	}
	HRet(bool isSuccess)
	{
		this->isSuccess = isSuccess;
	}
	bool getSuccess() {
		return isSuccess;
	}
	HObject* getObject() {
		return ret;
	}
	QString getReason() {
		return reason;
	}
private:
	bool isSuccess = false;
	HObject* ret = nullptr;
	QString reason;
};
