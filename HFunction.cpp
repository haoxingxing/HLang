#include "HFunction.h"
#include "HLang.h"
#include <QFile>
#include "HBuiltin.h"

HFunction::HFunction()
{
	DefineMemberFunction("add", &HFunction::add);
	DefineMemberFunction("exec", &HFunction::hexec);
	DefineMemberFunction("loadfile", &HFunction::loadfile);
	DefineMemberFunction("toString", &HFunction::toString);
	DefineMemberFunction("link", &HFunction::link);
	def->importclass("builtin", new HBuiltin);
}

HFunction::~HFunction()
{
	for (int i = 0; i < commands.length(); i++)
	{
		delete commands[i];
	}
	delete def;
}

HObject* HFunction::add(HArgs args)
{
	CheckArgs(1);
	if (HObjectHelper(args[0]).to<HString>() != nullptr)
	{
		commands.push_back(new QString(HObjectHelper(args[0]).to<HString>()->toQString()));
		return new HRet(true);
	}
	return new HRet(nullptr, false, WhyFunctionAddFailed);
}
HObject* HFunction::hexec(HArgs args)
{
	CheckArgs(0);
	for (int i = 0; i < commands.length(); i++)
	{
		HLangHelper::exec(*commands[i], def);
	}
	return new HRet(true);
}
HObject* HFunction::loadfile(HArgs args)
{
	CheckArgs(1);
	QString file_w = HObjectHelper(args[0]).to<HString>()->toQString();
	QFile file(file_w);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return new HRet(nullptr, false, WhyFunctionLoadFileFailed);
	while (!file.atEnd()) {
		QString str = file.readLine();
		str.simplified();
		if (!str.isEmpty() && !(str.at(0) == "#"))
			commands.push_back(new QString(str));
	}
	return new HRet(true);
}

HObject* HFunction::toString(HArgs args)
{
	CheckArgs(0);
	QString cs;
	for (int i = 0; i < commands.length(); i++)
		cs.append(*commands[i] + "\r\n");
	return new HRet(new HString(new QString(cs)));
}
HObject* HFunction::link(HArgs args)
{
	CheckArgs(2);
	if (HObjectHelper(args[0]).to<HString>() == nullptr)
		return new HRet(nullptr, false, WhyFunctionLinkFailed);
	def->importclass(HObjectHelper(args[0]).to<HString>()->toQString(), args[1]);
	return new HRet(true);
}