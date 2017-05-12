#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "AudioManager.h"
#include "PulsePlayer.h"

#include <QMainWindow>
#include <QMap>
#include <QPushButton>
#include <QSharedPointer>

namespace Ui {
class MainWindow;
}

enum MediaType
{
    MT_MEDIA,
    MT_NAVIGATION
};

Q_DECLARE_METATYPE(MediaType)

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

    struct UiPlayer
    {
        QSharedPointer<PulsePlayer> player;
        QPushButton* button;
        am::am_sourceID_t sourceID;
        am::am_mainConnectionID_t connectionID;
    };

    Ui::MainWindow *ui;
    QMap<MediaType, UiPlayer> mPlayers;
    AudioManager mAudioManager;

private slots:
    void onBtnPlay(bool checked);
    void onPlayerFinished();
};

#endif // MAINWINDOW_H
