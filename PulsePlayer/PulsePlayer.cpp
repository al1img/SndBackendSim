#include "PulsePlayer.h"

#include <QDebug>

#include <pulse/error.h>
#include <pulse/proplist.h>

PulsePlayer::PulsePlayer(const QString& fileName, const QString& mediaName,
                         uint8_t numChannels, uint32_t rate, pa_sample_format_t format) :
    mFile(fileName),
    mMediaName(mediaName),
    mNumChannels(numChannels),
    mRate(rate),
    mFormat(format)
{

}

PulsePlayer::~PulsePlayer()
{
    requestInterruption();
    wait();
}

void PulsePlayer::run()
{
    if (!mFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "Error open file:" << mFile.fileName();

        return;
    }

    const pa_sample_spec ss =
    {
        .format = mFormat,
        .rate = mRate,
        .channels = mNumChannels
    };

    int error = 0;

    pa_simple* pa = pa_simple_new(nullptr, "snd_be", PA_STREAM_PLAYBACK, nullptr,
                                  mMediaName.toLatin1().data(), &ss,
                                  nullptr, nullptr, &error);

    if (!pa)
    {
        qDebug() << "Error open pulse:" << pa_strerror(error);

        return;
    }

    QByteArray data = mFile.read(46);

    while(!isInterruptionRequested() && data.size())
    {
        data = mFile.read(1024);

        if (data.size())
        {
            if (pa_simple_write(pa, data.constData(), data.size(), &error) < 0)
            {
                qDebug() << "Error write pulse:" << pa_strerror(error) << "size:" << data.size();

                break;
            }
        }
    }

    pa_simple_drain(pa, nullptr);
    pa_simple_free(pa);

    mFile.close();
}
