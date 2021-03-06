/* Copyright (c) 2015, Niklas Hauser
 * All Rights Reserved.
 *
 * The file is part of the upainter library and is released under the GPLv3
 * license. See the file `LICENSE` for the full license governing this code.
 * ------------------------------------------------------------------------ */

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QWheelEvent>
#include <QGesture>
#include <QDebug>
#include <QTimer>
#include <QHBoxLayout>

modm::ges::Color
fromQColor(qreal h, qreal s, qreal l, qreal a = 1.0)
{
	QColor qcolor = QColor::fromHslF(h, s, l, a);
	return Color(qcolor.red(), qcolor.green(), qcolor.blue(), qcolor.alpha());
}


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	surface(buffer), painter(surface),
	qDisplay(surface), offset(0.7)
{
	ui->setupUi(this);

	this->setGeometry(0, 0, surface.getWidth() * 10+25, surface.getHeight()* 10+60);

	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(&qDisplay);
	setCentralWidget(new QWidget);
	centralWidget()->setLayout(layout);

	constexpr ColorRGB332 s(kColorBlack);
	static_assert(s.getValue() == 0, "kColorBlack is not black!");

	connect(&timer, &QTimer::timeout, [this]()
	{
		offset += 0.0007135;
		if (offset > 1) offset -= 1;

		/*
		surface.clear(Color::White);
		/*/
		for (int ww = 0; ww < surface.getWidth(); ww++)
		{
			for (int hh = 0; hh < surface.getHeight(); hh++)
			{
				qreal l = 1 - hh / qreal(surface.getHeight());
				qreal h = (ww / qreal(surface.getWidth()) + offset);
				if (h > 1) h -= 1;
				Color color = fromQColor(h, 1, l, 1);
				surface.setPixel(ww, hh, color);
//				surface.compositePixel(ww, hh, PixelColor<Format>::AlphaColor(color), Painter<Format>::AoverB);
			}
		}
		//*/

		qreal r = offset * 10;
		static float l = 10;
		l += 0.2;

		Rect clip = Rect(40 + int(-l/2) % 100, 20 +int(-l/4)%50, 60, 40);
		painter.resetClipArea();
		painter.fillRect(clip, kColorWhite);

		Rect outline = Rect(int(l)%130, int(l)%70, 60, 40);
		painter.setClipArea(Rect(20, 10, 127-40, 63-20));
		painter.drawRect(outline, fromQColor(offset, 1, 0.5, 0.5), painter.Plus);

		painter.setClipArea(clip);
		painter.fillRect(Rect(int(l)%160 - 20, int(l)%80 - 15, 10, 10), kColorBlue);

//		painter.drawLine(Line(64-128*sin(r), 32-128*cos(r), 64+128*sin(r), 32+128*cos(r)), Color::Red, clip);

		Line line(rand()%300-150, rand()%200 - 100, rand()%300 -150, rand()%200 - 100);
//		Line line(-141, 56, 110, 70);
//		qDebug() << "(" << line.getX1() << "," << line.getY1() << ") ---> (" << line.getX2() << "," << line.getY2() << ")";
		painter.resetClipArea();
		painter.drawLine(line, Color(0xff, 0, 0, 0x7f), painter.AoverB);
		painter.setClipArea(clip);
		painter.drawLine(line, kColorBlue);

		painter.drawLine(Line(40 + int(l)%30, 32-128*cos(r), 40 + int(l)%30, 32+128*cos(r)), kColorYellow);
		painter.drawLine(Line(64-128*sin(r), 20 - int(l)%30, 64+128*sin(r), 20 - int(l)%30), kColorGreen);

		painter.drawCircle(Circle(70 - int(l/2)%30, 25 - int(l/4)%40, abs(42 * sin(r))), kColorBlue);
		painter.resetClipArea();
		painter.fillCircle(Circle(64, 32, abs(35 * sin(r))), Color(0, 0, 255, 64), painter.AoverB);

		Ellipse el(Point(5, 7), Size(abs(62 * sin(r*1.1))*2, abs(40 * cos(r))*2));
		painter.drawEllipse(el, Color(255, 0, 255, 82), painter.AoverB);
		painter.setClipArea(clip);
		painter.drawEllipse(el, kColorRed);

		Ellipse el2(Point(60, 20), Size(abs(62 * sin(r)), abs(42 * sin(r))+1));
		painter.setClipArea(Rect(20, 10, 127-40, 63-20));
		painter.fillEllipse(el2, Color(255, 0, 0, 82), painter.AoverB);

		qDisplay.repaint();
	});
	timer.start(33);
}

MainWindow::~MainWindow()
{
	delete ui;
}
