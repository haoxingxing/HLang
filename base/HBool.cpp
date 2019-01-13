#include "HBool.h"
#include "HVoid.h"

bool HLang::HBool::value() const
{
	return data;
}

HPointer HLang::HBool::set(HArgs args)
{
	this->data = args[0]->to<HBool>()->value();
	return HPointer(HVoid::__new__(HArgs()));
}

HPointer HLang::HBool::init_bool(HArgs args)
{
	this->data = args[0]->to<HBool>()->value();
	return HPointer(HVoid::__new__(HArgs()));
}
HLang::HBool* HLang::HBool::setvalue(bool __data__ /*= false*/)
{
	this->data = __data__;
	return this;
}