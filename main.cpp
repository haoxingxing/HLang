﻿#include "HObject.h"
#include <QApplication>
#include "HBuiltin.h"
#include <iostream>
#include <QDebug>
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	HLang* HMain = new HLang(nullptr);
	HMain->importclass("builtin", new HBuiltin(HMain));
	if (argc == 2) {
		qDebug() << "The Model isn't ready";
		return 0;
	}
	else
	{
		while (true)
		{
			std::string in;
			QString a;
			while (in != "run") {
				a.append(QString::fromStdString(in));
				std::cin >> in;
			}
			HFunction m(HMain);
			m.fromString(HArgs({ new HString(a) }));
			m.run(HArgs());
		}
	}
	return app.exec();
}