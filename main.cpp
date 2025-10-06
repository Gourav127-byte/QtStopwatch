#include <QApplication>
#include <QWidget>
#include <QLCDNumber>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>

class Stopwatch : public QWidget
{
    Q_OBJECT

public:
    Stopwatch(QWidget *parent = nullptr) : QWidget(parent), hours(0), minutes(0), seconds(0), running(false)
    {
        lcd = new QLCDNumber(8, this);
        lcd->setSegmentStyle(QLCDNumber::Flat);
        lcd->display("00:00:00");

        startButton = new QPushButton("Start", this);
        resetButton = new QPushButton("Reset", this);

        QHBoxLayout *buttonLayout = new QHBoxLayout;
        buttonLayout->addWidget(startButton);
        buttonLayout->addWidget(resetButton);

        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        mainLayout->addWidget(lcd);
        mainLayout->addLayout(buttonLayout);
        setLayout(mainLayout);

        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &Stopwatch::updateTime);
        connect(startButton, &QPushButton::clicked, this, &Stopwatch::startStop);
        connect(resetButton, &QPushButton::clicked, this, &Stopwatch::reset);

        setWindowTitle("Stopwatch");
        resize(250, 150);
    }

private slots:
    void startStop()
    {
        if (!running) {
            timer->start(1000);
            startButton->setText("Stop");
            running = true;
        } else {
            timer->stop();
            startButton->setText("Start");
            running = false;
        }
    }

    void reset()
    {
        timer->stop();
        hours = minutes = seconds = 0;
        lcd->display("00:00:00");
        startButton->setText("Start");
        running = false;
    }

    void updateTime()
    {
        seconds++;
        if (seconds == 60) { seconds = 0; minutes++; }
        if (minutes == 60) { minutes = 0; hours++; }

        QString time = QString("%1:%2:%3")
                           .arg(hours, 2, 10, QChar('0'))
                           .arg(minutes, 2, 10, QChar('0'))
                           .arg(seconds, 2, 10, QChar('0'));
        lcd->display(time);
    }

private:
    QLCDNumber *lcd;
    QPushButton *startButton;
    QPushButton *resetButton;
    QTimer *timer;
    int hours, minutes, seconds;
    bool running;
};

#include "main.moc"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Stopwatch w;
    w.show();
    return app.exec();
}

