#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qdebug.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mPlayers[MT_MEDIA] =      {QSharedPointer<PulsePlayer>(new PulsePlayer("../Media/media.wav", "Media", 2, 44000, PA_SAMPLE_S16NE)),           ui->btnMedia,      100, 0};
    mPlayers[MT_NAVIGATION] = {QSharedPointer<PulsePlayer>(new PulsePlayer("../Media/navigation.wav", "Navigation", 2, 11000, PA_SAMPLE_S16NE)), ui->btnNavigation, 101, 0};

    auto it = mPlayers.begin();

    for(; it != mPlayers.end(); it++)
    {
        it.value().button->setProperty("type", it.key());
        it.value().player->setProperty("type", it.key());

        connect(it.value().player.data(), SIGNAL(finished()), this, SLOT(onPlayerFinished()));
        connect(it.value().button, SIGNAL(clicked(bool)), this, SLOT(onBtnPlay(bool)));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onBtnPlay(bool checked)
{
    MediaType type = sender()->property("type").value<MediaType>();

    if (checked)
    {
        qDebug() << "Play:" << mPlayers[type].button->text() << "type:" << type;

        mPlayers[type].connectionID = mAudioManager.connect(mPlayers[type].sourceID);

        mPlayers[type].player->start();
        mPlayers[type].button->setChecked(true);
    }
    else
    {
        qDebug() << "Stop:" << mPlayers[type].button->text() << "type:" << type;
        mPlayers[type].player->requestInterruption();
        mPlayers[type].player->wait();
    }
}

void MainWindow::onPlayerFinished()
{
    MediaType type = sender()->property("type").value<MediaType>();

    if (mPlayers[type].button->isChecked())
    {
        mPlayers[type].button->setChecked(false);

        qDebug() << "Stop:" << mPlayers[type].button->text() << "type:" << type;
    }

    mAudioManager.disconnect(mPlayers[type].connectionID);
}
