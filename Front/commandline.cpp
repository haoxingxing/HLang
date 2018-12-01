﻿#include "commandline.h"
#include "ui_commandline.h"
#include <QDebug>
#include "HBuiltin.h"
#include <functional>
commandline::commandline(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::commandline)
{
	ui->setupUi(this);
	def->importclass("builtin", new HBuiltin(def));
}

commandline::~commandline()
{
	delete ui;
	delete def;
}

void commandline::add(QString str)
{
	ui->textBrowser->append(str);
}

void commandline::on_lineEdit_returnPressed()
{
	QString _command = ui->lineEdit->text();
	if (_command == "reload_builtin")
		def->importclass("builtin", new HBuiltin(def));
	if (_command == "reload")
	{
		delete def;
		def = new HLang(nullptr);
		def->importclass("builtin", new HBuiltin(def));
	}
	ui->textBrowser->setText(ui->textBrowser->document()->toPlainText() + _command);
	HLangHelper::exec(_command, def, this);
	ui->textBrowser->append(">>");
	ui->textBrowser->moveCursor(QTextCursor::End);
	ui->lineEdit->clear();
}