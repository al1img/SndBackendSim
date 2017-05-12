#ifndef PULSEPLAYER_H
#define PULSEPLAYER_H

#include <QFile>
#include <QThread>

#include <pulse/simple.h>

class PulsePlayer : public QThread
{
    Q_OBJECT

public:
    PulsePlayer(const QString& fileName, const QString& mediaName,
                uint8_t numChannels, uint32_t rate, pa_sample_format_t format);
    ~PulsePlayer();

private:
    QFile mFile;
    QString mMediaName;
    uint8_t mNumChannels;
    uint32_t mRate;
    pa_sample_format_t mFormat;

    void run() override;
};

#endif // PULSEPLAYER_H
