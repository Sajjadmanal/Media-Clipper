
#include "videoplayer.h"

#include <QtWidgets>
#include <qvideowidget.h>
#include <qvideosurfaceformat.h>
#include <QMediaRecorder>

VideoPlayer::VideoPlayer(QWidget *parent)
    : QWidget(parent)
    , mediaPlayer(0, QMediaPlayer::VideoSurface)
    , positionSlider(0)
    , playButton(0)
    , recordButton(0)
    , errorLabel(0)
{

    QVideoWidget *videoWidget = new QVideoWidget;


    QAbstractButton *openButton = new QPushButton(tr("Open..."));
    connect(openButton, SIGNAL(clicked()), this, SLOT(openFile()));

    QAbstractButton *recordButton = new QPushButton(tr("Record"));
    connect(recordButton, SIGNAL(clicked()), this, SLOT(record()));

    playButton = new QPushButton;
    playButton->setEnabled(false);
    playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

    connect(playButton, SIGNAL(clicked()),
            this, SLOT(play()));



    positionSlider = new QSlider(Qt::Horizontal);
    positionSlider->setRange(0, 0);

    connect(positionSlider, SIGNAL(sliderMoved(int)),
            this, SLOT(setPosition(int)));

    errorLabel = new QLabel;
    errorLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

    QBoxLayout *controlLayout = new QHBoxLayout;
    controlLayout->setMargin(10);
    controlLayout->addWidget(openButton);
    controlLayout->addWidget(recordButton);
    controlLayout->addWidget(playButton);
    controlLayout->addWidget(positionSlider);

    QBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(controlLayout);
    layout->addWidget(videoWidget);
    layout->addWidget(errorLabel);
    setLayout(layout);

    mediaPlayer.setVideoOutput(videoWidget);
    connect(&mediaPlayer, SIGNAL(stateChanged(QMediaPlayer::State)),
            this, SLOT(mediaStateChanged(QMediaPlayer::State)));
    connect(&mediaPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    connect(&mediaPlayer, SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));
    connect(&mediaPlayer, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(handleError()));
}

VideoPlayer::~VideoPlayer()
{


}

void VideoPlayer::play()
{
    switch(mediaPlayer.state()) {
    case QMediaPlayer::PlayingState:
        mediaPlayer.pause();
        break;
    default:
        mediaPlayer.play();

        break;

    }
}

void VideoPlayer::openFile()
{
    errorLabel->setText("");

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open this video"),QDir::homePath());

    if (!fileName.isEmpty()) {
        mediaPlayer.setMedia(QUrl::fromLocalFile(fileName));
        playButton->setEnabled(true);

    }
}

void VideoPlayer::record()
{


        QMediaRecorder *mediaRecorder = new QMediaRecorder(&mediaPlayer);
        QString file = "home/lastec/record.avi";
        QFile file1(file);
        file1.open(QIODevice::WriteOnly);
        mediaRecorder->setContainerFormat("avi");
        mediaRecorder->setOutputLocation(QUrl::fromLocalFile(file));
        mediaRecorder->record();


    }



void VideoPlayer::mediaStateChanged(QMediaPlayer::State state)
{
    switch(state) {
    case QMediaPlayer::PlayingState:
        playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        break;
    default:
        playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        break;
    }
}

void VideoPlayer::positionChanged(qint64 position)
{
    positionSlider->setValue(position);
}

void VideoPlayer::durationChanged(qint64 duration)
{
    positionSlider->setRange(0, duration);
}

void VideoPlayer::setPosition(int position)
{
    mediaPlayer.setPosition(position);
}

void VideoPlayer::handleError()
{
    playButton->setEnabled(false);
    errorLabel->setText("Error: " + mediaPlayer.errorString());
}
